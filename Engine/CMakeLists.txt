cmake_minimum_required(VERSION 3.13)

project(Engine)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# GLAD
add_subdirectory(Contrib/Glad)

include_directories(include)

file(GLOB_RECURSE HEADERS src/*.hpp) #TODO: CHANGE THESE
file(GLOB_RECURSE SOURCES src/*.cpp) #TODO: CHANGE THESE

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} GLAD glfw pthread)