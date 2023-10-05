cmake_minimum_required(VERSION 3.26)
project(Comp345_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Comp345_Project
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        CardsDriver.h
        GameEngine.cpp
        GameEngine.h
        GameEngineDriver.cpp
        GameEngineDriver.h
        MainDriver.cpp
        map.cpp
        map.h
        MapDriver.cpp
        MapDriver.h
        MapLoader.cpp
        MapLoader.h
        Orders.cpp
        Orders.h
        OrdersDriver.cpp
        OrdersDriver.h
        Player.cpp
        Player.h
        PlayerDriver.cpp
        PlayerDriver.h)
