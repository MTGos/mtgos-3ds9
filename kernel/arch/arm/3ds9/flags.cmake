SET(PLATFORM_C_FLAGS "-I../../kernel/arch/arm/3ds9/include -mcpu=arm946e-s -march=armv5te -mthumb-interwork -marm -O9")
SET(PLATFORM_CXX_FLAGS "${PLATFORM_C_FLAGS}")
SET(PLATFORM_ASM_FLAGS "${PLATFORM_C_FLAGS}")
