cmake_minimum_required(VERSION 3.0.0)

project(a.out)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}//)

file(GLOB SRC "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} progbase m)

set(CMAKE_C_FLAGS "g++ *.cpp -std=c++17 -pedantic-errors -Wall -Werror -Wno-unused")
