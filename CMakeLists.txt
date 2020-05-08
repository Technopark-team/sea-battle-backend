cmake_minimum_required(VERSION 3.14)

project(seabattle C CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost ${BOOST_VERSION} COMPONENTS thread system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(Boost_LIBRARY_DIR /usr/local/lib)
link_directories(${Boost_LIBRARY_DIR})

set(SEABATTLE_CLI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sbcli")

set(CLIENT_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/seabattle_cli.cpp)
set(SERVER_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server.cpp)

add_subdirectory(${SEABATTLE_CLI_LIB})

# compile client
add_executable(seabattle-cli ${CLIENT_SRC_LIST})
target_link_libraries(seabattle-cli sbcli)
target_link_libraries(seabattle-cli ${Boost_LIBRARIES})

# compile server
add_executable(test_tcp_server ${SERVER_SRC_LIST})
target_link_libraries(test_tcp_server ${Boost_LIBRARIES})

message("Boost version ${Boost_VERSION} found at ${Boost_LIBRARY_DIRS}")