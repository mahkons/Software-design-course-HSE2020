cmake_minimum_required(VERSION 3.0) # Проверка версии CMake
project(CLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pedantic")

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
)

include_directories(inc/)
add_executable(cli ${SOURCES})
