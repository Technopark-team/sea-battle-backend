project(sbcli CXX)
set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SRC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES ${SRC_DIR}/core/*.cpp
        ${SRC_DIR}/network/*.cpp
        ${SRC_DIR}/serialization/*.cpp
        ${SRC_DIR}/controller/*.cpp
        ${SRC_DIR}/model/*.cpp
        ${SRC_DIR}/view/*.cpp
        ${SRC_DIR}/validation/*.cpp
        ${SRC_DIR}/components/menu/*.cpp
        ${SRC_DIR}/components/auth/*.cpp)

file(GLOB HEADERS ${SRC_DIR}/core/*.h
        ${SRC_DIR}/config/*.h
        ${SRC_DIR}/network/*.h
        ${SRC_DIR}/serialization/*.h
        ${SRC_DIR}/controller/*.h
        ${SRC_DIR}/model/*.h
        ${SRC_DIR}/view/*.h
        ${SRC_DIR}/validation/*.h
        ${SRC_DIR}/components/menu/*.h
        ${SRC_DIR}/components/auth/*.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})