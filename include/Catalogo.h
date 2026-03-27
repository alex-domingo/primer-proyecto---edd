#ifndef PROYECTO_EDD_CATALOGO_H
#define PROYECTO_EDD_CATALOGO_H

#include "producto.h"

/*
 * catalogo.h
 * ----------
 * El Catálogo es el "jefe" del sistema. Él tiene una instancia de
 * cada estructura de datos y se encarga de mantenerlas sincronizadas.
 *
 * Cuando alguien quiere agregar, buscar o eliminar un producto,
 * siempre habla con el Catálogo — nunca con las estructuras directo.
 *
 * Por ahora solo es el esqueleto; iremos llenando los métodos
 * conforme avancemos en las fases del proyecto.
 *
 * Estructuras que va a coordinar:
 *   - ListaSimple      (fase 1)
 *   - ListaOrdenada    (fase 1)
 *   - ArbolAVL         (fase 2)
 *   - TablaHash        (fase 3)
 *   - ArbolB           (fase 4)
 *   - ArbolBPlus       (fase 5)
 */

// Por ahora hacemos forward declarations para no depender
// de headers que todavía no existen. Los iremos agregando fase a fase.
class ListaSimple;
class ListaOrdenada;
class ArbolAVL;
class TablaHash;
class ArbolB;
class ArbolBPlus;

class Catalogo {
private:
    // Punteros a cada estructura — se inicializan en el constructor
    ListaSimple *listaSimple;
    ListaOrdenada *listaOrdenada;
    ArbolAVL *arbolAVL;
    TablaHash *tablaHash;
    ArbolB *arbolB;
    ArbolBPlus *arbolBPlus;

public:
    // Constructor y destructor
    Catalogo();

    ~Catalogo();

    // -- Operaciones principales --

    // Agrega un producto en TODAS las estructuras (con rollback si falla)
    bool agregarProducto(const Producto &producto);

    // Elimina un producto de TODAS las estructuras
    bool eliminarProducto(const std::string &codigoBarra);

    // -- Búsquedas (cada una usa la estructura más adecuada) --

    // Busca por nombre usando el AVL
    Producto *buscarPorNombre(const std::string &nombre);

    // Busca por código de barra usando la tabla hash
    Producto *buscarPorCodigo(const std::string &codigo);

    // Retorna todos los productos de una categoría (árbol B+)
    // TODO: cambiar void* por el tipo de colección que definamos
    void buscarPorCategoria(const std::string &categoria);

    // Retorna productos cuya fecha caiga en el rango dado (árbol B)
    void buscarPorRangoFecha(const std::string &fechaInicio,
                             const std::string &fechaFin);

    // Lista todos los productos ordenados por nombre (AVL in-order)
    void listarPorNombre();

    // -- Utilidades --
    int contarProductos() const;
};

#endif //PROYECTO_EDD_CATALOGO_H
