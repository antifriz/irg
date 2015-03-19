cmake_minimum_required(VERSION 2.8)
project(irg.labosi.ciklus1.vjezba1)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../../lib")

add_executable(vjezba1.testniZadaci testniZadaci.cpp)
target_link_libraries(vjezba1.testniZadaci LINK_PUBLIC linAlgLib)

add_executable(vjezba1.zadatak1 zadatak1.cpp)
target_link_libraries(vjezba1.zadatak1 LINK_PUBLIC linAlgLib)

add_executable(vjezba1.zadatak2 zadatak2.cpp)
target_link_libraries(vjezba1.zadatak2 LINK_PUBLIC linAlgLib)

add_executable(vjezba1.zadatak3 zadatak3.cpp)
target_link_libraries(vjezba1.zadatak3 LINK_PUBLIC linAlgLib)

