cmake_minimum_required(VERSION 2.8)
project(vjezba9)

include_directories("${PROJECT_SOURCE_DIR}/../../linAlgLib")

file(GLOB src
*.cpp
)

add_executable(${PROJECT_NAME}_zadatak1 ${src})
target_link_libraries(${PROJECT_NAME}_zadatak1 LINK_PUBLIC linAlgLib GL GLU glut)
