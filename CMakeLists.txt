cmake_minimum_required(VERSION 3.21)
project(PureC C)

set(CMAKE_C_STANDARD 99)

add_executable(PureC main.c QuickSort.h MST.c QuickSort.c TopoSort.c HuffmanTree.c EditDistance.c Dijkstra.c AVLTree.c HuffmanTree.h EditDistance.h MST.h  TopoSort.h Dijkstra.h)
