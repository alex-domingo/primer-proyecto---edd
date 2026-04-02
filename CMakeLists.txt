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
        src/Catalogo.cpp
        include/NodoLista.h
        include/ListaSimple.h
        include/ListaOrdenada.h
        src/NodoLista.cpp
        src/ListaSimple.cpp
        src/ListaOrdenada.cpp
        include/NodoAVL.h
        include/ArbolAVL.h
        src/NodoAVL.cpp
        src/ArbolAVL.cpp
        include/NodoB.h
        include/ArbolB.h
        src/NodoB.cpp
        src/ArbolB.cpp
        include/NodoBPlus.h
        include/ArbolBPlus.h
        src/NodoBPlus.cpp
        src/ArbolBPlus.cpp
        include/CargadorCSV.h
        src/CargadorCSV.cpp
        include/MedidorRendimiento.h
        src/MedidorRendimiento.cpp
        include/VisualizadorDot.h
        src/VisualizadorDot.cpp
)
