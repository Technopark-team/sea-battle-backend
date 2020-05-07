cmake_minimum_required(VERSION 3.14)

project(seabattle C CXX)
set(CMAKE_CXX_STANDARD 17)

set(CLIENT_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/seabattle_cli.cpp)

set(SEABATTLE_CLI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sbcli")

add_subdirectory(${SEABATTLE_CLI_LIB})

# compile client
add_executable(seabattle-cli ${CLIENT_SRC_LIST})
target_link_libraries(seabattle-cli sbcli)