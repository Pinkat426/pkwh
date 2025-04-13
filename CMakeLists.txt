cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME H7_APP)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# 启用 ARM CMSIS DSP 库宏定义（针对 Cortex-M7）
add_compile_definitions(
    ARM_MATH_CM7
    ARM_MATH_MATRIX_CHECK
    ARM_MATH_ROUNDING
)

# 编译器选项：开启硬件浮点并指定浮点单元为 M7 所用的 fpv5
add_compile_options(
    -mcpu=cortex-m7
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
    -ffunction-sections
    -fdata-sections
    -fno-common
    -fmessage-length=0
)

# 链接器选项：与编译器匹配的浮点配置
add_link_options(
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
)


# 自动添加 RTT 目录下的所有 .c 文件
file(GLOB RTT_SOURCES JLINK_Debug/RTT/*.c)
file(GLOB_RECURSE BSP_SOURCES BSP/*.c)
file(GLOB_RECURSE APP APP/*.c)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
    # Add user defined sources here
                BSP/ws2812.c
                ${RTT_SOURCES}  # 将所有 RTT 目录下的 .c 文件加入
                ${BSP_SOURCES}
                ${APP}
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    BSP
    BSP/bsp_led
    BSP/bsp_key
    JLINK_Debug
    JLINK_Debug/RTT
    APP
    APP/comm_task
    APP/key_task
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)


target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
-u _printf_float
)


