cmake_minimum_required(VERSION 3.29)
project(M1OEP_lvagtben)

set(CMAKE_CXX_STANDARD 14)

add_executable(M1OEP_lvagtben
    main.cpp
        inventory.h
        equipment.h
        inventory.cpp
        equipment.cpp
        character.cpp
        character.h
        Party.cpp
        Party.h)
