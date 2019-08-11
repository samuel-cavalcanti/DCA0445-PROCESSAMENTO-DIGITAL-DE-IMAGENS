
cmake_minimum_required (VERSION 2.6)
project (swapRegions)

find_package( OpenCV REQUIRED ) 

set(CMAKE_CXX_STANDARD 11)



add_executable(swapRegions
	       swapRegions.cpp)
           

target_link_libraries( swapRegions ${OpenCV_LIBS} )






