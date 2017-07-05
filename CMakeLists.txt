cmake_minimum_required(VERSION 3.7)
project(IconResizer)

find_package(OpenCV 3.2.0 REQUIRED)
find_package(Boost 1.58 COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(IconResizer ${SOURCE_FILES})
target_link_libraries(IconResizer ${OpenCV_LIBS} ${Boost_LIBRARIES})
