cmake_minimum_required(VERSION 3.1)
project(irg.labosi.prvi)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../lib")

add_executable(testniZadaci testniZadaci.cpp)
target_link_libraries(testniZadaci LINK_PUBLIC linAlgLib)

add_executable(zadatak1 zadatak1.cpp)
target_link_libraries(zadatak1 LINK_PUBLIC linAlgLib)

add_executable(zadatak2 zadatak2.cpp)
target_link_libraries(zadatak2 LINK_PUBLIC linAlgLib)

add_executable(zadatak3 zadatak3.cpp)
target_link_libraries(zadatak3 LINK_PUBLIC linAlgLib)

