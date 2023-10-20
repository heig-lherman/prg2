cmake_minimum_required(VERSION 3.22)
project(PRG2_L2_parking C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Wpadded -Wvla -Wpedantic -Wformat -pedantic -lm")

# fsanitizer
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,alignment,signed-integer-overflow,shift,integer-divide-by-zero,null -fstack-protector -fno-sanitize-recover=null")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,alignment,signed-integer-overflow,shift,integer-divide-by-zero,null -fstack-protector -fno-sanitize-recover=null")
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(L2-parking main.c vehicule.c affichage.c taxation.c statistique.c parking.c parking.h)
