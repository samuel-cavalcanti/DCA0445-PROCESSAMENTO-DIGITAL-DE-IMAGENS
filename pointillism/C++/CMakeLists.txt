cmake_minimum_required(VERSION 3.15)
project(C__)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(cannypoints cannypoints.cpp)

add_executable(canny canny.cpp)

add_executable(pointillism pointillism.cpp)

target_link_libraries(pointillism ${OpenCV_LIBS})

target_link_libraries(canny ${OpenCV_LIBS})

target_link_libraries(cannypoints ${OpenCV_LIBS})