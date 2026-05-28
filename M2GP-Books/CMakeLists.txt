cmake_minimum_required(VERSION 3.20)
project(Polymorphism)

set(CMAKE_CXX_STANDARD 17)

add_executable(Polymorphism main.cpp Book.cpp Book.h Audio_Book.cpp Audio_Book.h)
