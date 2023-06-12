cmake_minimum_required(VERSION 3.24)
project(ParadProjekt-master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ParadProjekt-master
        main.cpp
        patch.cpp
        patch.h
        player.cpp
        player.h
        world.cpp
        world.h "IEntities.cpp" "IEntities.h" PowerUps.h PowerUps.cpp)