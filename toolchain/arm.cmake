cmake_minimum_required(VERSION 3.28)

if (PROJECT_IS_TOP_LEVEL AND NOT IN_TRY_COMPILE)
    # include(FetchContent)
    #
    # # Declare the exact version you want (update version or URL as needed)
    # FetchContent_Declare(
    #     GCC_ARM_EMBEDDED
    #     URL      https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
    #     SOURCE_DIR ${CMAKE_BINARY_DIR}/toolchains
    # )
    #
    # if (NOT GCC_ARM_EMBEDDED_POPULATED)
    #     message(STATUS "[INFO] Downloading GNU Arm Embedded Toolchain...")
    #     FetchContent_Populate(GCC_ARM_EMBEDDED)
    # endif()
    #
    # # Set paths to the extracted binaries:
    # set(ARM_GCC_PATH "${CMAKE_BINARY_DIR}/toolchains/bin")
    # set(CMAKE_C_COMPILER   "${ARM_GCC_PATH}/arm-none-eabi-gcc")
    # set(CMAKE_CXX_COMPILER "${ARM_GCC_PATH}/arm-none-eabi-g++")
    # set(CMAKE_ASM_COMPILER "${ARM_GCC_PATH}/arm-none-eabi-gcc")
    # set(CMAKE_OBJCOPY      "${ARM_GCC_PATH}/arm-none-eabi-objcopy")
endif()
