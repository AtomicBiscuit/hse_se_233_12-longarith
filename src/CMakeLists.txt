add_executable(LongArithmetic main.cpp)

target_link_libraries(LongArithmetic PRIVATE BigFloat)

target_include_directories(LongArithmetic PRIVATE
        "${PROJECT_SOURCE_DIR}/lib"
)