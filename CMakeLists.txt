cmake_minimum_required(VERSION 3.12)
project(time-test-facility LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-O3 -Wall -Wextra -Wpedantic)
endif()

find_package(OpenSSL REQUIRED)

add_executable(main
    src/cpp/main.cpp
)

target_include_directories(main PRIVATE
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(main PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
)
