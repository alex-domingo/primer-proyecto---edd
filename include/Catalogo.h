#ifndef PROYECTO_EDD_CATALOGO_H
#define PROYECTO_EDD_CATALOGO_H

#include "Producto.h"
#include "ListaSimple.h"
#include "ListaOrdenada.h"
#include "ArbolAVL.h"
#include "ArbolB.h"
#include "ArbolBPlus.h"

/*
 * Catalogo.h
 * -----------
 * El Catálogo es el orquestador central del sistema.
 * Coordina las 5 estructuras de datos simultáneamente
 * y garantiza que siempre estén sincronizadas.
 *
 * La operación más delicada es agregarProducto():
 * usa inserción atómica — si falla en cualquier estructura,
 * hace rollback en todas las que ya insertaron.
 *
 * Estructuras coordinadas:
 *   listaSimple   — búsqueda secuencial (referencia para benchmarks)
 *   listaOrdenada — búsqueda secuencial ordenada (referencia)
 *   arbolAVL      — búsqueda por nombre O(log n)
 *   arbolB        — búsqueda por rango de fecha O(log n + k)
 *   arbolBPlus    — búsqueda por categoría O(log n + k)
 */

class Catalogo {
private:
    ListaSimple *listaSimple;
    ListaOrdenada *listaOrdenada;
    ArbolAVL *arbolAVL;
    ArbolB *arbolB;
    ArbolBPlus *arbolBPlus;

    int totalProductos;

    // Verifica si ya existe un producto con ese código de barra
    bool existeCodigo(const std::string &codigoBarra) const;

public:
    Catalogo();

    ~Catalogo();

    // Agrega en TODAS las estructuras — rollback si falla alguna
    bool agregarProducto(const Producto &producto);

    // Elimina de TODAS las estructuras
    bool eliminarProducto(const std::string &nombre,
                          const std::string &codigoBarra,
                          const std::string &categoria,
                          const std::string &fechaCaducidad);

    // -- Búsquedas --
    Producto *buscarPorNombre(const std::string &nombre);

    void buscarPorCategoria(const std::string &categoria);

    void buscarPorRangoFecha(const std::string &inicio,
                             const std::string &fin);

    // -- Listados --
    void listarPorNombre() const;

    void listarSimple() const;

    void listarOrdenado() const;

    int contarProductos() const;

    bool estaVacio() const;

    // -- Acceso a estructuras internas (para el medidor de rendimiento) --
    ListaSimple *obtenerListaSimple() const { return listaSimple; }
    ListaOrdenada *obtenerListaOrdenada() const { return listaOrdenada; }
    ArbolAVL *obtenerArbolAVL() const { return arbolAVL; }
};

#endif //PROYECTO_EDD_CATALOGO_H
