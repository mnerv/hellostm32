cmake_minimum_required(VERSION 3.28)
project(hellostm32 VERSION 0.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # Group CMake targets inside a folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # Generate compile_commands.json for language servers
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps")

set(INC_FILES "")
set(SRC_FILES
    src/main.cpp
    src/syscall.cpp
    src/sysmeme.cpp
)
add_executable(fw ${INC_FILES} ${SRC_FILES})
target_include_directories(fw
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
target_compile_features(fw PRIVATE c_std_23 cxx_std_23)
target_compile_options(fw
    PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -Wpedantic
    -Wshadow
    -Werror
    # hardware flags
    -mcpu=cortex-m33
    -mfloat-abi=hard   # FPU is hardware
    -mfpu=fpv5-sp-d16  # fp version 5, single precision, 16-double-precision-register
    -mthumb
    -nostdlib
    # cpp flags
    -fno-rtti
    -fno-exceptions
    -fno-threadsafe-statics
)
target_link_options(fw PRIVATE 
    -mcpu=cortex-m33
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)
target_compile_definitions(fw
    PRIVATE
    ""
)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${INC_FILES} ${SRC_FILES})
