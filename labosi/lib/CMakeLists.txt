set(SOURCE_FILES AbstractVector.cpp Vector.cpp AbstractMatrix.cpp Matrix.cpp MatrixTransposeView.cpp MatrixSubMatrixView.cpp MatrixVectorView.cpp)

add_library(linAlgLib ${SOURCE_FILES})
target_include_directories(linAlgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

