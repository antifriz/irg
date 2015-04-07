cmake_minimum_required(VERSION 2.8)
project(irg.labosi.ciklus2.vjezba4)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../../lib")

add_executable(vjezba4.zadatak1 zadatak1.cpp)
target_link_libraries(vjezba4.zadatak1 LINK_PUBLIC linAlgLib GL GLU glut)
