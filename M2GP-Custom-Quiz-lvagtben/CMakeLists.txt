cmake_minimum_required(VERSION 3.15)
project(M2GP_Custom_Quiz)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp Question.cpp Question.h Quiz.cpp Quiz.h)
# TODO Uncomment this line to create an executable for your testing program
#add_executable(test testing.cpp Question.cpp Question.h Quiz.cpp Quiz.h)