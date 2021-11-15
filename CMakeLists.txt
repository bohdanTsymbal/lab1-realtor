cmake_minimum_required(VERSION 3.20)
project(lab1_realtor)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_realtor main.cpp DataProcessing.cpp DataProcessing.h RealEstate.h LinearAlgebra.cpp LinearAlgebra.h LinearRegression.cpp LinearRegression.h)
