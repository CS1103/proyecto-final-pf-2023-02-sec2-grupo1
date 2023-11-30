cmake_minimum_required(VERSION 3.26)
project(proyecto-final-pf-2023-02-sec2-grupo1)

set(CMAKE_CXX_STANDARD 20)

include_directories(./Prototype_0.5)
file(GLOB source_files
        main.cpp
        Prototype_0.5/*.cpp)

add_executable(proyecto-final-pf-2023-02-sec2-grupo1 ${source_files})
