cmake_minimum_required(VERSION 3.28)
project(unicesumar_aula4 C)

set(CMAKE_C_STANDARD 11)

add_executable(unicesumar_aula4 main.c
        ex1_pilhas/ex1_pilhas.c
        ex2_filas/ex2_filas.c
        ex1_pilhas/ex1_pilhas.h
        navegacao.h
        ex2_filas/ex2_filas.h)
