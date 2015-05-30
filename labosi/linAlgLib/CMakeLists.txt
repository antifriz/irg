cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3 -flto -DNDEBUG")


set(SOURCE_FILES AbstractVector.cpp Vector.cpp AbstractMatrix.cpp Matrix.cpp MatrixSubMatrixView.cpp MatrixTransposeView.cpp MatrixVectorView.cpp VectorMatrixView.cpp IRG.cpp)

add_library(linAlgLib ${SOURCE_FILES})
target_include_directories(linAlgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

