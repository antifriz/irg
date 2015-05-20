cmake_minimum_required(VERSION 2.8)
project(vjezba8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../../linAlgLib")

add_executable(${PROJECT_NAME}_zadatak1 zadatak1.cpp)
target_link_libraries(${PROJECT_NAME}_zadatak1 LINK_PUBLIC linAlgLib GL GLU glut)
