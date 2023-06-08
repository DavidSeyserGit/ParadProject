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
        utility.cpp
        utility.h
        world.cpp
        world.h entities.cpp entities.h Camel.cpp Camel.h)