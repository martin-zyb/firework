cmake_minimum_required (VERSION 2.8)

project (firework)

include_directories(".//vendor")

FILE(GLOB DIR_SOURCES "*source//*.cpp" "*source//*.h" "*source//*.rc")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

add_executable(firework ${DIR_SOURCES})