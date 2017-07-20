SET(PLATFORM_C_FLAGS "-I../../kernel/arch/arm/3ds11/include -mcpu=cortex-a7 -mlittle-endian -mtune=cortex-a7 -mfloat-abi=hard -mtp=soft -O2")
SET(PLATFORM_CXX_FLAGS "${PLATFORM_C_FLAGS}")
SET(PLATFORM_ASM_FLAGS "${PLATFORM_C_FLAGS}")
