cmake_minimum_required(VERSION 3.13)

project(GLAD)
#set(CMAKE_C_FLAGS "-fpic")
include_directories(include)
add_library(${PROJECT_NAME} src/glad.c)