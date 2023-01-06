cmake_minimum_required(VERSION 3.21)
project(numerosBipolares C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c codigo/bipolarInts.c headers/bipolarInts.h codigo/bipolarChars.c headers/bipolarChars.h codigo/users.c headers/users.h codigo/key_holder.c headers/key_holder.h)
