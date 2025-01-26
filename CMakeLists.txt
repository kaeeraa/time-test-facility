cmake_minimum_required(VERSION 3.20)
project(time-test-facility)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(loop-cos-cpp src/cpp/loop-cos/main.cpp)

add_executable(loop-cos-cpp-test tests/cpp/loop-cos/main_test.cpp)

target_link_libraries(loop-cos-cpp-test PRIVATE GTest::GTest GTest::Main)
gtest_discover_tests(loop-cos-cpp-test)