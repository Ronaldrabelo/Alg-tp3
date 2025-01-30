cmake_minimum_required(VERSION 3.29)
project(Alg_tp3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Alg_tp3 main.cpp
        include/algorithms/Greedy.h
        src/utils/GraphUtils.cpp
        include/utils/GraphUtils.h
        include/utils/PermutationUtils.h
        src/utils/PermutationUtils.cpp
        include/algorithms/BruteForce.h
        src/algorithms/DynamicProgramming.cpp
        src/algorithms/BruteForce.cpp
        include/algorithms/DynamicProgramming.h
        src/algorithms/Greedy.cpp)
