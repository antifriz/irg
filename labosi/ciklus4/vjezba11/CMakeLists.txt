cmake_minimum_required(VERSION 2.8)
project(vjezba11)

include_directories("${PROJECT_SOURCE_DIR}/../../linAlgLib")

add_executable(${PROJECT_NAME}_zadatak1 zadatak1.cpp)
target_link_libraries(${PROJECT_NAME}_zadatak1 LINK_PUBLIC linAlgLib GL GLU glut)

add_executable(${PROJECT_NAME}_zadatak2 zadatak2.cpp)
target_link_libraries(${PROJECT_NAME}_zadatak2 LINK_PUBLIC linAlgLib GL GLU glut)
