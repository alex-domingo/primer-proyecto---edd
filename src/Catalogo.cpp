#include "catalogo.h"
#include <iostream>

/*
 * catalogo.cpp
 * ------------
 * Implementación del orquestador central.
 * Por ahora los métodos están vacíos (retornan nullptr o no hacen nada).
 * Los iremos completando fase a fase conforme implementemos
 * cada estructura de datos.
 *
 * Fase actual: 0 — solo esqueleto
 */

Catalogo::Catalogo() {
    // Por ahora inicializamos todo en nullptr
    // Cuando implementemos cada estructura, la crearemos aquí
    listaSimple = nullptr;
    listaOrdenada = nullptr;
    arbolAVL = nullptr;
    arbolB = nullptr;
    arbolBPlus = nullptr;

    std::cout << "[Catalogo] Sistema iniciado correctamente.\n";
}

Catalogo::~Catalogo() {
    // Cuando las clases estén implementadas, aquí liberamos su memoria.
    // Por ahora todos son nullptr así que no hay nada que borrar todavía.
    // (Los delete se irán descomentando fase a fase)

    // delete listaSimple;
    // delete listaOrdenada;
    // delete arbolAVL;
    // delete tablaHash;
    // delete arbolB;
    // delete arbolBPlus;
}

// Agrega el producto en todas las estructuras
// Todavía no implementado — se completa en fase 5
bool Catalogo::agregarProducto(const Producto &producto) {
    // TODO: implementar inserción atómica con rollback (fase 6)
    std::cout << "[TODO] agregarProducto: " << producto.nombre << "\n";
    return false;
}

// Elimina el producto de todas las estructuras
bool Catalogo::eliminarProducto(const std::string &codigoBarra) {
    // TODO: implementar eliminación propagada (fase 6)
    std::cout << "[TODO] eliminarProducto: " << codigoBarra << "\n";
    return false;
}

Producto *Catalogo::buscarPorNombre(const std::string &nombre) {
    // TODO: delegar al AVL (fase 6)
    std::cout << "[TODO] buscarPorNombre: " << nombre << "\n";
    return nullptr;
}

Producto *Catalogo::buscarPorCodigo(const std::string &codigo) {
    // TODO: delegar a la tabla hash (fase 6)
    std::cout << "[TODO] buscarPorCodigo: " << codigo << "\n";
    return nullptr;
}

void Catalogo::buscarPorCategoria(const std::string &categoria) {
    // TODO: delegar al árbol B+ (fase 6)
    std::cout << "[TODO] buscarPorCategoria: " << categoria << "\n";
}

void Catalogo::buscarPorRangoFecha(const std::string &fechaInicio,
                                   const std::string &fechaFin) {
    // TODO: delegar al árbol B (fase 6)
    std::cout << "[TODO] buscarPorRangoFecha: "
            << fechaInicio << " - " << fechaFin << "\n";
}

void Catalogo::listarPorNombre() {
    // TODO: recorrido in-order del AVL (fase 6)
    std::cout << "[TODO] listarPorNombre\n";
}

int Catalogo::contarProductos() const {
    // TODO: llevar un contador interno (fase 6)
    return 0;
}
