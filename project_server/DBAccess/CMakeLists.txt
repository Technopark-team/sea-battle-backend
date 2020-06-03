#include_directories(${includes_l})
project(DBAccess CXX)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SRC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

file(GLOB HEADERS ${SRC_DIR}/include/*.h)

#add_library(DBAccess_lib SHARED ${PROJECT_SOURCE_DIR}/DBAccess.cpp ${SOURCES} ${HEADERS})
add_library(DBAccess_lib ${SOURCES} ${HEADERS})
target_include_directories(DBAccess_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_path(HIREDIS_HEADER hiredis)
target_include_directories(DBAccess_lib PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(DBAccess_lib  ${HIREDIS_LIB})

find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(DBAccess_lib PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(DBAccess_lib ${REDIS_PLUS_PLUS_LIB})
