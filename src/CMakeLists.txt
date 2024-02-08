add_library(Pi pi.cpp)
target_link_libraries(Pi PRIVATE BigFloat)


add_executable(LongArithmetic main.cpp)
target_link_libraries(LongArithmetic PRIVATE Pi)


target_include_directories(Pi PRIVATE
        "${PROJECT_SOURCE_DIR}/lib"
)

target_include_directories(LongArithmetic PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
)