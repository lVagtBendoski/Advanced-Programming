cmake_minimum_required(VERSION 3.8)
project(Monsters)

set(CMAKE_CXX_STANDARD 17)

add_executable(Water_Monster
        Water_Monsters/Water_Monster.cpp
        Water_Monsters/Water_Monster_Main.cpp
        Water_Monsters/Lake_Monster.cpp
        Water_Monsters/Sea_Monster.cpp)
add_executable(Water_Monster_Testing
        Water_Monsters/Water_Monster.cpp
        Water_Monsters/Water_Monster_Testing.cpp
        Water_Monsters/Lake_Monster.cpp
        Water_Monsters/Sea_Monster.cpp)
add_executable(Darkness_Monster_Main
        Darkness_Monsters/Darkness_Monster.cpp
        Darkness_Monsters/Closet_Monster.cpp
        Darkness_Monsters/Under_Bed_Monster.cpp
        Darkness_Monsters/Darkness_Monster_Main.cpp)
add_executable(Darkness_Monster_Testing
        Darkness_Monsters/Darkness_Monster.cpp
        Darkness_Monsters/Closet_Monster.cpp
        Darkness_Monsters/Darkness_Monster_Testing.cpp
        Darkness_Monsters/Under_Bed_Monster.cpp)
#TODO: Uncomment this line once you create Sky_Monster.h and Sky_Monster.cpp in the Sky_Monsters folder
add_executable(Sky_Monster_Testing
        Sky_Monsters/Sky_Monster.cpp
        Sky_Monsters/Cloud_Monster.cpp
        Sky_Monsters/Comet_Monster.cpp
        Sky_Monsters/Sky_Monster_Testing.cpp
        Sky_Monsters/Sky_Monster.cpp)

