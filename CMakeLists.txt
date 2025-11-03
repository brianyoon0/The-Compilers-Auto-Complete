cmake_minimum_required(VERSION 3.26)
project(The_Compilers)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(The-Compilers
        src/main.cpp
        src/Trie.cpp
        src/TST.cpp
        include/Trie.h
        include/TST.h
)
