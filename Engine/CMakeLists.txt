cmake_minimum_required(VERSION 3.13)

project(Engine)

add_subdirectory(Contrib/Glad)

include_directories(src)

set(HEADERS src/core/math/linearalgebra/Vector.hpp src/core/math/linearalgebra/Matrix.hpp src/graphics/Window.hpp src/core/string/NString.hpp)
set(SOURCES src/graphics/Window.cpp src/core/string/NString.cpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})