cmake_minimum_required(VERSION 3.21)
project(framebench LANGUAGES CXX)

add_executable(framebench src/main.cpp)
target_compile_features(framebench PRIVATE cxx_std_20)
set_target_properties(framebench PROPERTIES CXX_EXTENSIONS OFF)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME summarize
        COMMAND framebench "${CMAKE_CURRENT_SOURCE_DIR}/tests/frames.csv")
    set_tests_properties(summarize PROPERTIES
        PASS_REGULAR_EXPRESSION "frames=4 p50_ms=10.000 p95_ms=40.000 p99_ms=40.000")

    add_test(NAME reject_invalid
        COMMAND framebench "${CMAKE_CURRENT_SOURCE_DIR}/tests/invalid.csv")
    set_tests_properties(reject_invalid PROPERTIES WILL_FAIL TRUE)
endif()
