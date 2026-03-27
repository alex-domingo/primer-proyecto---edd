cmake_minimum_required(VERSION 3.20)
project(proyecto_edd)

# Usamos C++17, que tiene todo lo que necesitamos para el proyecto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Le decimos a CMake dónde están los headers (.h)
include_directories(include)

# Recopilamos todos los .cpp de src/ automáticamente
file(GLOB_RECURSE SOURCES "src/*.cpp")

# El ejecutable se arma con main.cpp y todos los fuentes de src/
add_executable(proyecto_edd main.cpp ${SOURCES}
        include/Producto.h
        src/Producto.cpp
        include/Catalogo.h
        src/Catalogo.cpp)
