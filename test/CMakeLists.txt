add_executable(LongArithmeticTest test.cpp)

add_custom_target(start_test COMMAND LongArithmeticTest)

target_link_libraries(LongArithmeticTest PRIVATE gtest_main Pi BigFloat)

target_include_directories(LongArithmeticTest PRIVATE
        "${PROJECT_SOURCE_DIR}/lib"
        "${PROJECT_SOURCE_DIR}/src"
)