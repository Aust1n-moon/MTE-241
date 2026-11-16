set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# On PATH when configured through the STM32 extension (cube-cmake); the bundle
# glob is the fallback for plain cmake.
file(GLOB _st_gcc_dirs "$ENV{HOME}/.local/share/stm32cube/bundles/gnu-tools-for-stm32/*/bin")
find_program(CMAKE_C_COMPILER arm-none-eabi-gcc HINTS ENV GCC_TOOLCHAIN_ROOT ${_st_gcc_dirs} REQUIRED)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})

# Same flags STM32CubeIDE uses for this project (see Debug/Core/Src/subdir.mk)
set(_mcu "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb --specs=nano.specs")
set(CMAKE_C_FLAGS_INIT "${_mcu} -ffunction-sections -fdata-sections -Wall -fstack-usage")
set(CMAKE_ASM_FLAGS_INIT "${_mcu} -x assembler-with-cpp")
set(CMAKE_C_FLAGS_DEBUG_INIT "-O0 -g3")
set(CMAKE_ASM_FLAGS_DEBUG_INIT "-g3")
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
