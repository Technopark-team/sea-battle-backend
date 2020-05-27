cmake_minimum_required(VERSION 3.14)

project(seabattle C CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -std=c++17 -lncursesw -DNCURSES_NOMACROS")
#set(CMAKE_CXX_CPPLINT "cpplint")

find_package(Boost ${BOOST_VERSION} COMPONENTS thread system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CURSES_INCLUDE_DIR})

set(Boost_LIBRARY_DIR /usr/local/lib)
link_directories(${Boost_LIBRARY_DIR})

set(SEABATTLE_CLI_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sbcli")
set(SEABATTLE_UTILS_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sbutils")

set(CLIENT_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/seabattle_cli.cpp)
set(SERVER_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/tcp_server.cpp)
set(TEST_UI ${CMAKE_CURRENT_SOURCE_DIR}/test_ui.cpp)

find_package(GTest REQUIRED)
find_package(msgpack REQUIRED)
find_package(Curses REQUIRED)

set(GMock_INCLUDE_DIR "/usr/local/include")
if (EXISTS "/usr/local/lib/libgmock.a")
    set(GMock_LIBRARY "/usr/local/lib/libgmock.a")
    set(GMock_LIBRARY_MAIN "/usr/local/lib/libgmock_main.a")
    message("Gmock is a static build")
else ()
    set(GMock_LIBRARY "/usr/local/lib/libgmock.so")
    set(GMock_LIBRARY "/usr/local/lib/libgmock.so")
    message("Gmock is a dynamic build")
endif ()
set(GMock_BOTH_LIBRARIES ${GMock_LIBRARY} ${GMock_LIBRARY_MAIN})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMock_INCLUDE_DIR})

add_subdirectory(${SEABATTLE_CLI_LIB})
add_subdirectory(${SEABATTLE_UTILS_LIB})

# compile client
add_executable(seabattle-cli ${CLIENT_SRC_LIST})
target_link_libraries(seabattle-cli sbcli)
target_link_libraries(seabattle-cli sbutils)
target_link_libraries(seabattle-cli ${Boost_LIBRARIES})
target_link_libraries(seabattle-cli ${msgpack_LIBRARIES})
target_link_libraries(seabattle-cli ${CURSES_LIBRARIES})

# compile server
add_executable(test_tcp_server ${SERVER_SRC_LIST})
target_link_libraries(test_tcp_server sbutils)
target_link_libraries(test_tcp_server ${Boost_LIBRARIES})
target_link_libraries(test_tcp_server ${msgpack_LIBRARIES})

# compile test_ui
add_executable(test_ui ${TEST_UI})
target_link_libraries(test_ui ${CURSES_LIBRARIES})

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

######sbcli test sources########
file(GLOB TEST_CLI_SOURCES ${TESTS_DIR}/tests_cli/run_tests.cpp)
file(GLOB TEST_CLI_HEADERS ${TESTS_DIR}/tests_cli/*.h ${TESTS_DIR}/tests_cli/controller/*.h)

add_executable(run-cli-tests ${TEST_CLI_SOURCES} ${TEST_CLI_HEADERS})
target_link_libraries(run-cli-tests ${GTEST_BOTH_LIBRARIES})
target_link_libraries(run-cli-tests ${GMock_BOTH_LIBRARIES})
target_link_libraries(run-cli-tests ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(run-cli-tests ${Boost_LIBRARIES})
target_link_libraries(run-cli-tests sbcli)
target_link_libraries(run-cli-tests sbutils)

message("Boost version ${Boost_VERSION} found at ${Boost_LIBRARY_DIRS}")