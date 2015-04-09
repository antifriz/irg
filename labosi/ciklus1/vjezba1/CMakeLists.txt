cmake_minimum_required(VERSION 2.8)
project(vjezba1)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -g")

include_directories("${PROJECT_SOURCE_DIR}/../../linAlgLib")

add_executable(${PROJECT_NAME}_testniZadaci testniZadaci.cpp)
target_link_libraries(${PROJECT_NAME}_testniZadaci LINK_PUBLIC linAlgLib)

add_executable(${PROJECT_NAME}_zadatak1 zadatak1.cpp)
target_link_libraries(${PROJECT_NAME}_zadatak1 LINK_PUBLIC linAlgLib)

add_executable(${PROJECT_NAME}_zadatak2 zadatak2.cpp)
target_link_libraries(${PROJECT_NAME}_zadatak2 LINK_PUBLIC linAlgLib)

add_executable(${PROJECT_NAME}_zadatak3 zadatak3.cpp)
target_link_libraries(${PROJECT_NAME}_zadatak3 LINK_PUBLIC linAlgLib)

