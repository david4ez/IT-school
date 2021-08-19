cmake_minimum_required(VERSION 3.0.2)
project(task_1)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(task_1 main.cpp fingerprint.h fingerprint.cpp)

target_link_libraries(task_1 OpenSSL::Crypto)
target_link_libraries(task_1 OpenSSL::SSL)
