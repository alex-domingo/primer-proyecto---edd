#ifndef PROYECTO_EDD_PRODUCTO_H
#define PROYECTO_EDD_PRODUCTO_H

#include <string>

/*
 * producto.h
 * ----------
 * Aquí definimos la estructura base de un producto del supermercado.
 * Todos los demás módulos del proyecto van a trabajar con esta clase,
 * así que es importante tenerla bien definida desde el principio.
 *
 * Campos según el documento del proyecto:
 *   - nombre       : clave para el árbol AVL
 *   - codigoBarra  : clave única para la tabla hash
 *   - categoria    : clave para el árbol B+
 *   - fechaCaducidad: clave para el árbol B (formato YYYY-MM-DD)
 *   - marca, precio, stock: datos adicionales del producto
 */

class Producto {
public:
    std::string nombre;
    std::string codigoBarra; // debe ser único en todo el catálogo
    std::string categoria;
    std::string fechaCaducidad; // formato ISO: "YYYY-MM-DD"
    std::string marca;
    double precio;
    int stock;

    // Constructor por defecto — lo necesitamos para crear nodos vacíos
    Producto();

    // Constructor completo — el que más vamos a usar al cargar el CSV
    Producto(const std::string &nombre,
             const std::string &codigoBarra,
             const std::string &categoria,
             const std::string &fechaCaducidad,
             const std::string &marca,
             double precio,
             int stock);

    // Muestra los datos del producto en consola (útil para pruebas)
    void mostrar() const;

    // Compara dos productos por nombre (para el AVL)
    bool operator<(const Producto &otro) const;

    bool operator==(const Producto &otro) const;
};

#endif //PROYECTO_EDD_PRODUCTO_H
