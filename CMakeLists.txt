cmake_minimum_required(VERSION 3.12)
project(Compiler_of_Clit)

set(CMAKE_CXX_STANDARD 11)

add_executable(Compiler_of_Clit main.cpp Clite_lex.cpp Clite_lex.h SymTable.cpp SymTable.h Clite_parse.cpp Clite_parse.h)