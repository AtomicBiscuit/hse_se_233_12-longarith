cmake_minimum_required(VERSION 3.10)

project(LongArithmetic VERSION 1.9)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)

add_executable(LongArithmetic main.cpp)

target_link_libraries(LongArithmetic PUBLIC BigFloat)

target_include_directories(LongArithmetic PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/lib"
)
