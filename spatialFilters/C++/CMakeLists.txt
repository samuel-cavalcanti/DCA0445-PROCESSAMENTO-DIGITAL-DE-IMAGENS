cmake_minimum_required(VERSION 3.14)
project(C__)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(C__ addweighted.cpp)

target_link_libraries( C__ ${OpenCV_LIBS} )