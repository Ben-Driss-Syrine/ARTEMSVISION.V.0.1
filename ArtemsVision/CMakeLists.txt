cmake_minimum_required(VERSION 3.25)
project(ArtemsVision)

set(CMAKE_CXX_STANDARD 17)

add_executable(ArtemsVision source.cpp PexelProcessor.h PixelOptimizer.h PixelEvaluation.h)
