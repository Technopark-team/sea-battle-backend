cmake_minimum_required(VERSION 3.14)
project(project_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++1z -g -I msgpack-c/include -pthread -fPIC")

find_package(Threads)

set(project_name project_server)
set(library_name server_lib)
include_directories(/usr/local/include/)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

set(includes ${PROJECT_SOURCE_DIR}/include)
include_directories(${includes})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${library_name} SHARED ${sources})
target_include_directories(${library_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_path(HIREDIS_HEADER hiredis)
target_include_directories(${library_name} PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(${library_name}  ${HIREDIS_LIB})

find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(${library_name} PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(${library_name} ${REDIS_PLUS_PLUS_LIB})

add_subdirectory(DBAccess)

add_executable(project_server main.cpp)
target_link_libraries(${project_name} ${library_name} DBAccess_lib)

enable_testing()
add_subdirectory(test)
