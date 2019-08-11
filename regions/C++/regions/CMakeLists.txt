
cmake_minimum_required (VERSION 2.6)
project (regions)

find_package( OpenCV REQUIRED ) 

set(CMAKE_CXX_STANDARD 11)



add_executable(regions
	       regions.cpp)
           

target_link_libraries( regions ${OpenCV_LIBS} )




