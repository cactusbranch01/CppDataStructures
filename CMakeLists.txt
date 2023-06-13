cmake_minimum_required(VERSION 3.24)
project(dataStructuresC__)

set(CMAKE_CXX_STANDARD 17)

add_executable(dataStructuresC__ main.cpp queue.cpp queue.h stack.cpp stack.h linkedList.cpp linkedList.h node.cpp node.h hash.h hash.cpp)
