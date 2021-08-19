cmake_minimum_required(VERSION 3.0.2)
project(writer)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.76.0 COMPONENTS program_options)

add_executable(writer main.cpp)

include_directories(writer ${Boost_INCLUDE_DIRS})
target_link_libraries(writer ${Boost_LIBRARIES})
