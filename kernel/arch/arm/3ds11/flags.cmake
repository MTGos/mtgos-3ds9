SET(PLATFORM_C_FLAGS "-I../../kernel/arch/arm/3ds11/include -mcpu=mpcore -mlittle-endian -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -O9")
SET(PLATFORM_CXX_FLAGS "${PLATFORM_C_FLAGS}")
SET(PLATFORM_ASM_FLAGS "${PLATFORM_C_FLAGS}")
