cmake_minimum_required(VERSION 3.13)

project(Sandbox)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(CMAKE_CXX_STANDARD 20)

include_directories(../Engine/include)

file(GLOB_RECURSE HEADERS src/*.hpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Engine)
