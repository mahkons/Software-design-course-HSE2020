cmake_minimum_required(VERSION 3.0) # Проверка версии CMake
project(CLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pedantic -pthread")

set(SOURCES 
    src/main.cpp
    src/application.cpp
    src/environment.cpp
    src/executor.cpp
    src/parser/parser.cpp
    src/parser/tokenizer.cpp
    src/parser/variables_substitutor.cpp
    src/parser/commands_parser.cpp
    src/commands/command_factory.cpp

    src/commands/wc_command.cpp
    src/commands/echo_command.cpp
    src/commands/exit_command.cpp
    src/commands/pwd_command.cpp
    src/commands/cat_command.cpp
    src/commands/assignment_command.cpp
    src/commands/external_command.cpp
)

include_directories(inc/)

#header only libraries
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost COMPONENTS filesystem REQUIRED)

add_executable(cli ${SOURCES})
target_link_libraries(cli ${Boost_LIBRARIES})
