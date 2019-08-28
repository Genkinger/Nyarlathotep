cmake_minimum_required(VERSION 3.13)

project(Sandbox)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/Engine/src)
add_executable(${PROJECT_NAME} src/main.cpp ../Engine/src/core/string/NString.cpp ../Engine/src/core/string/NString.hpp ../Engine/src/core/math/linearalgebra/Matrix.hpp
        ../Engine/src/core/math/linearalgebra/Vector.hpp  ../Engine/src/core/math/linearalgebra/Ray.hpp)
