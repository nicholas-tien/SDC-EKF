cmake_minimum_required(VERSION 3.7)
project(carn_term2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/KalmanFilter.cpp
        src/FusionEKF.cpp
        src/Tools.cpp)
add_executable(carn_term2 ${SOURCE_FILES})