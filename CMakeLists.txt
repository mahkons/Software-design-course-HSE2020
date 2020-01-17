cmake_minimum_required(VERSION 3.0) # Проверка версии CMake
project(CLI)

set(CMAKE_CXX_FLAGS 
        "${CMAKE_CXX_FLAGS}
        -Wall,
        -Wextra,
        -Werror,
        -pedantic,
        -std=c++17,
        -xc++"
        )
 

add_executable(main main.cpp)
