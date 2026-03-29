#include "Catalogo.h"
#include <iostream>

/*
 * Catalogo.cpp
 * -------------
 * Implementación del orquestador central del sistema.
 *
 * La clave de esta clase es la INSERCIÓN ATÓMICA:
 * insertamos en cada estructura una por una. Si alguna falla
 * (por ejemplo, código de barra duplicado), revertimos todas
 * las inserciones previas y reportamos el error.
 *
 * El orden de inserción es:
 *   1. listaSimple
 *   2. listaOrdenada
 *   3. arbolAVL
 *   4. arbolB
 *   5. arbolBPlus
 *
 * Si falla en el paso N, eliminamos de las estructuras 1..N-1.
 */

Catalogo::Catalogo() : totalProductos(0) {
    listaSimple = new ListaSimple();
    listaOrdenada = new ListaOrdenada();
    arbolAVL = new ArbolAVL();
    arbolB = new ArbolB();
    arbolBPlus = new ArbolBPlus();

    std::cout << "[Catalogo] Sistema iniciado. Estructuras listas.\n";
}

Catalogo::~Catalogo() {
    delete listaSimple;
    delete listaOrdenada;
    delete arbolAVL;
    delete arbolB;
    delete arbolBPlus;
}

// Busca en la lista simple para verificar duplicados de código de barra
bool Catalogo::existeCodigo(const std::string &codigoBarra) const {
    return listaSimple->buscarPorCodigo(codigoBarra) != nullptr;
}

// ============================================================
// Inserción atómica con rollback
// ============================================================

bool Catalogo::agregarProducto(const Producto &producto) {
    // Validación previa: código de barra duplicado
    if (existeCodigo(producto.codigoBarra)) {
        std::cout << "[Catalogo] ERROR: codigo de barra '"
                << producto.codigoBarra << "' ya existe. Operacion cancelada.\n";
        return false;
    }

    // Validaciones básicas de datos
    if (producto.nombre.empty() || producto.codigoBarra.empty() ||
        producto.categoria.empty() || producto.fechaCaducidad.empty()) {
        std::cout << "[Catalogo] ERROR: producto con campos vacios. Operacion cancelada.\n";
        return false;
    }

    if (producto.precio < 0 || producto.stock < 0) {
        std::cout << "[Catalogo] ERROR: precio o stock negativos. Operacion cancelada.\n";
        return false;
    }

    // --- Inserción paso a paso con rollback ---

    // Paso 1: Lista simple
    listaSimple->insertar(producto);

    // Paso 2: Lista ordenada
    listaOrdenada->insertar(producto);

    // Paso 3: AVL — puede fallar si el nombre ya existe (clave duplicada)
    int tamAVLAntes = arbolAVL->obtenerTamano();
    arbolAVL->insertar(producto);
    if (arbolAVL->obtenerTamano() == tamAVLAntes) {
        // El AVL rechazó la inserción (nombre duplicado)
        // Rollback: revertimos lista simple y ordenada
        listaSimple->eliminar(producto.codigoBarra);
        listaOrdenada->eliminar(producto.codigoBarra);
        std::cout << "[Catalogo] ERROR: nombre '" << producto.nombre
                << "' ya existe en el AVL. Rollback aplicado.\n";
        return false;
    }

    // Paso 4: Árbol B (por fecha)
    arbolB->insertar(producto);

    // Paso 5: Árbol B+ (por categoría)
    arbolBPlus->insertar(producto);

    totalProductos++;
    return true;
}

// ============================================================
// Eliminación propagada
// ============================================================

bool Catalogo::eliminarProducto(const std::string &nombre,
                                const std::string &codigoBarra,
                                const std::string &categoria,
                                const std::string &fechaCaducidad) {
    // Verificamos que exista antes de intentar eliminar
    if (!existeCodigo(codigoBarra)) {
        std::cout << "[Catalogo] ERROR: producto no encontrado. Nada que eliminar.\n";
        return false;
    }

    // Eliminamos de las 5 estructuras
    listaSimple->eliminar(codigoBarra);
    listaOrdenada->eliminar(codigoBarra);
    arbolAVL->eliminar(nombre);
    arbolB->eliminar(fechaCaducidad);
    arbolBPlus->eliminar(categoria, codigoBarra);

    totalProductos--;
    return true;
}

// ============================================================
// Búsquedas
// ============================================================

Producto *Catalogo::buscarPorNombre(const std::string &nombre) {
    // El AVL es la estructura óptima para esto — O(log n)
    Producto *resultado = arbolAVL->buscar(nombre);
    if (!resultado) {
        std::cout << "[Catalogo] Producto '" << nombre << "' no encontrado.\n";
    }
    return resultado;
}

void Catalogo::buscarPorCategoria(const std::string &categoria) {
    // El árbol B+ recorre las hojas enlazadas — O(log n + k)
    arbolBPlus->buscarPorCategoria(categoria);
}

void Catalogo::buscarPorRangoFecha(const std::string &inicio,
                                   const std::string &fin) {
    // El árbol B soporta rangos de forma nativa — O(log n + k)
    arbolB->buscarRango(inicio, fin);
}

// ============================================================
// Listados
// ============================================================

void Catalogo::listarPorNombre() const {
    std::cout << "=== Listado por nombre (AVL in-order) ===\n";
    arbolAVL->listarEnOrden();
}

void Catalogo::listarSimple() const {
    std::cout << "=== Listado lista simple (orden de insercion) ===\n";
    listaSimple->listar();
}

void Catalogo::listarOrdenado() const {
    std::cout << "=== Listado lista ordenada (alfabetico) ===\n";
    listaOrdenada->listar();
}

int Catalogo::contarProductos() const {
    return totalProductos;
}

bool Catalogo::estaVacio() const {
    return totalProductos == 0;
}
