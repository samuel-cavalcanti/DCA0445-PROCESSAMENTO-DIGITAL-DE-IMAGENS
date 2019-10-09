cmake_minimum_required(VERSION 3.15)
project(C__)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(homomorphicFilter homomorphicFilter.cpp)

add_executable(dft dft.cpp mat.cpp)

target_link_libraries(homomorphicFilter ${OpenCV_LIBS})

target_link_libraries(dft ${OpenCV_LIBS})
