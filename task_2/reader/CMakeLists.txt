cmake_minimum_required(VERSION 3.0.2)
project(reader)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.76.0 COMPONENTS program_options)

add_executable(reader main.cpp)

include_directories(reader ${Boost_INCLUDE_DIRS})
target_link_libraries(reader ${Boost_LIBRARIES})
