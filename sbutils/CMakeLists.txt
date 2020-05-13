project(sbutils CXX)
set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SRC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES ${SRC_DIR}/data/*.cpp
        ${SRC_DIR}/serialization/*.cpp)

file(GLOB HEADERS ${SRC_DIR}/data/*.h
        ${SRC_DIR}/serialization/*.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})