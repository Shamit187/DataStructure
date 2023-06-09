cmake_minimum_required(VERSION 3.17)
project(GraphModuleC__)

set(CMAKE_CXX_STANDARD 14)

add_executable(GraphModuleC__ main.cpp Implementation/AdjList.cpp HeaderFiles/AdjList.h Implementation/AdjListW.cpp HeaderFiles/AdjListW.h HeaderFiles/CustomExceptions.h HeaderFiles/FileUtility.h Implementation/AdjMatrix.cpp HeaderFiles/AdjMatrix.h)