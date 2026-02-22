cmake_minimum_required(VERSION 3.28)
project(hellostm32 VERSION 0.0.0 LANGUAGES C CXX ASM)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/Targets.cmake)
include(cmake/MCU.cmake)

add_compile_options(
    $<$<CONFIG:Debug>:-g3>
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:RelWithDebInfo>:-O2>
    $<$<CONFIG:RelWithDebInfo>:-g3>
)

add_subdirectory(lib)

add_exec(fw
    "src/main.c"
    "src/syscalls.c"
    "src/sysmem.c"
    INC ${PROJECT_SOURCE_DIR}/src
    LIBS bsp hal cmsis
)

# startup must be linked whole so Reset_Handler and the vector table are never
# dropped by --gc-sections (nothing in application code references them directly)
target_link_libraries(fw PRIVATE -Wl,--whole-archive startup -Wl,--no-whole-archive)

set(_LINKER_SCRIPT "${MCU_LINKER_SCRIPT}")
target_link_options(fw PRIVATE
    -T${_LINKER_SCRIPT}
    -Wl,-Map=${CMAKE_BINARY_DIR}/output.map
)
set_target_properties(fw PROPERTIES
    OUTPUT_NAME   firmware
    SUFFIX        .elf
    LINK_DEPENDS  ${_LINKER_SCRIPT}
)

# firmware.bin — raw binary for flashing
add_custom_command(
    TARGET fw POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:fw> ${CMAKE_BINARY_DIR}/firmware.bin
    COMMENT "Generating firmware.bin"
)
