cmake_minimum_required(VERSION 3.29)
project(M1OEP_lvagtben2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(M1OEP_lvagtben2
    character.cpp
    character.h
    equipment.cpp
    equipment.h
    inventory.cpp
    inventory.h
    main.cpp
    Party.cpp
    Party.h)
