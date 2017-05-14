CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
ENABLE_LANGUAGE(C CXX ASM-ATT)
FILE(GLOB SRCS *.c *.s)
FILE(GLOB_RECURSE FATFS_SRCS fatfs/*.c fatfs/*.s)
SET(CMAKE_ASM-ATT_COMPILE_OBJECT "<CMAKE_C_COMPILER> -g -x assembler-with-cpp -c -o -mcpu=arm946e-s -march=armv5te -o <OBJECT> <SOURCE>")
SET(CMAKE_C_FLAGS "-g -w -Werror -Wno-unused -Wno-unused-variable -mcpu=arm946e-s -march=armv5te -I.. -fno-stack-protector -nostdinc -ffreestanding -std=c11 -fno-builtin -w -Werror -nostdlib -fpie")
ADD_EXECUTABLE(arm9loaderhax.elf ${SRCS} ${FATFS_SRCS})
SET_TARGET_PROPERTIES(arm9loaderhax.elf PROPERTIES LINK_FLAGS "-T ../bootloader.ld")
TARGET_LINK_LIBRARIES(arm9loaderhax.elf gcc)
ADD_CUSTOM_COMMAND(TARGET arm9loaderhax.elf
                   POST_BUILD
                   COMMAND $ENV{HOME}/opt/bin/arm-none-eabi-objcopy -O binary arm9loaderhax.elf arm9loaderhax.bin)
