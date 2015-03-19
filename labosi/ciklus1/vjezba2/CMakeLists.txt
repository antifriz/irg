cmake_minimum_required(VERSION 2.8)
project(irg.labosi.ciklus1.vjezba2)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../../lib")

add_executable(ciklus2.zadatak1 zadatak1.cpp)
target_link_libraries(ciklus2.zadatak1 LINK_PUBLIC linAlgLib)
