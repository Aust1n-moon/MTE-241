cmake_minimum_required(VERSION 3.22)
project(ece350_start C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Globbed like CubeIDE does, so new files in Core/Src are picked up automatically
file(GLOB SOURCES CONFIGURE_DEPENDS
    Core/Src/*.c
    Core/Src/*.s
    Core/Startup/*.s
    Drivers/STM32F4xx_HAL_Driver/Src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX .elf
    LINK_DEPENDS "${CMAKE_SOURCE_DIR}/STM32F401RETX_FLASH.ld"  # relink when the script changes
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    USE_HAL_DRIVER
    STM32F401xE
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
)

target_link_options(${PROJECT_NAME} PRIVATE
    "-T${CMAKE_SOURCE_DIR}/STM32F401RETX_FLASH.ld"
    "-Wl,-Map=${PROJECT_NAME}.map"
)
