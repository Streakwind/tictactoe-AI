cmake_minimum_required(VERSION 3.10)
project(tictactoe_ai)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

include_directories(include)

set(SOURCES 
    src/main.cpp
    src/board.cpp
    src/agent.cpp
)

add_executable(tictactoe ${SOURCES})
