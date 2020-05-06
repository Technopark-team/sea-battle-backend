cmake_minimum_required(VERSION 3.14)
project(sea_battle_backend)

set(CMAKE_CXX_STANDARD 17)

add_executable(sea_battle_backend main.cpp sbcli/core/game_client.cpp sbcli/core/game_client.h)