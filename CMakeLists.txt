cmake_minimum_required(VERSION 3.25)
project(HW_BST_y_AVL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW_BST_y_AVL
        avl.h
        bst.h
        main.cpp)
