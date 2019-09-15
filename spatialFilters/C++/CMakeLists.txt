cmake_minimum_required(VERSION 3.14)
project(C__)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(addweighted addweighted.cpp)

add_executable(tiltshift tiltshift.cpp TiltShiftClass.cpp TiltShiftClass.h)

add_executable(laplgauss laplgauss.cpp laplgauss.cpp Menu.cpp Menu.h)

target_link_libraries( addweighted ${OpenCV_LIBS} )

target_link_libraries( tiltshift ${OpenCV_LIBS} )

target_link_libraries( laplgauss ${OpenCV_LIBS} )

