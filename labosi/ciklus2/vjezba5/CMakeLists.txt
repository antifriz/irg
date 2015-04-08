cmake_minimum_required(VERSION 2.8)
project(irg.labosi.ciklus2.vjezba5)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../../lib")

add_executable(vjezba5.zadatak1 zadatak1.cpp)
target_link_libraries(vjezba5.zadatak1 LINK_PUBLIC linAlgLib GL GLU glut)
