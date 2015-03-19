set(SOURCE_FILES AbstractVector.cpp Vector.cpp AbstractMatrix.cpp Matrix.cpp MatrixSubMatrixView.cpp MatrixTransposeView.cpp MatrixVectorView.cpp VectorMatrixView.cpp)

add_library(linAlgLib ${SOURCE_FILES} ForwardDeclarations.h)
target_include_directories(linAlgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

