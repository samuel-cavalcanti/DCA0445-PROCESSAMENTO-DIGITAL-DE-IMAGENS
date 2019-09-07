
cmake_minimum_required (VERSION 2.6)
project (histogram)

find_package( OpenCV REQUIRED )
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lvlc")


add_executable(equalize
	       equalize.cpp)

add_executable(motionDetector
	       motionDetector.cpp)


target_link_libraries( motionDetector ${OpenCV_LIBS} )

target_link_libraries( equalize ${OpenCV_LIBS} )



