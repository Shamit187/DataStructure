cmake_minimum_required(VERSION 3.20)
project(HashTableAnalysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashTableAnalysis main.cpp HashUtil.h ChainHash.h DoubleHasing.h CustomProbing.h)
