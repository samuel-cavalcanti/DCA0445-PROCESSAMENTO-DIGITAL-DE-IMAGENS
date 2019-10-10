cmake_minimum_required(VERSION 3.15)
project(C__)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)


add_executable(kmeans_test kmeansTest.cpp)

add_executable(kmeans kmeans.cpp)

target_link_libraries(kmeans_test ${OpenCV_LIBS})

target_link_libraries(kmeans ${OpenCV_LIBS})