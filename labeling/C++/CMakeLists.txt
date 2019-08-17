
cmake_minimum_required (VERSION 2.6)
project (labeling)

find_package( OpenCV REQUIRED ) 

set(CMAKE_CXX_STANDARD 11)



add_executable(labeling
	       labeling.cpp)
           

target_link_libraries( labeling ${OpenCV_LIBS} )




