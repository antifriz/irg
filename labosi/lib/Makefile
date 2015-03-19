PROJECT = linAlgLib
SOURCE = Vector.cpp AbstractVector.cpp
HEADERS = IVector.hpp AbstractVector.hpp
CXX = g++
CXXFLAGS = -Wall -g -std=c++0x 

OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	ar rcs $(PROJECT) $(OBJECTS)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core *.gch