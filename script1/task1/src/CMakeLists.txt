cmake_minimum_required(VERSION 2.8)

project(helloWorld)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(helloWorld helloWorld.cpp)

target_link_libraries(helloWorld ${ITK_LIBRARIES})