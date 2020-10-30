cmake_minimum_required(VERSION 3.13)
project(C_Module C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Module DjikstraAdjacencyList.c QuadTree.c cmake-build-debug/QuadTree.h dummy.c labelingalg.c auxfunc.c auxfunc.h driver.c auxlabel.c auxlabel.h)