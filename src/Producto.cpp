#include "Producto.h"
#include <iostream>
#include <iomanip>

/*
 * producto.cpp
 * ------------
 * Implementación de los métodos de la clase Producto.
 * Nada muy complicado aquí, básicamente constructores
 * y un método para mostrar la info en pantalla.
 */

// Constructor por defecto — valores vacíos/cero
Producto::Producto()
    : nombre(""), codigoBarra(""), categoria(""),
      fechaCaducidad(""), marca(""), precio(0.0), stock(0) {
}

// Constructor completo — asigna todos los campos de una vez
Producto::Producto(const std::string &nombre,
                   const std::string &codigoBarra,
                   const std::string &categoria,
                   const std::string &fechaCaducidad,
                   const std::string &marca,
                   double precio,
                   int stock)
    : nombre(nombre), codigoBarra(codigoBarra), categoria(categoria),
      fechaCaducidad(fechaCaducidad), marca(marca),
      precio(precio), stock(stock) {
}

// Imprime los datos del producto de forma legible
void Producto::mostrar() const {
    std::cout << "------------------------------\n";
    std::cout << "Nombre       : " << nombre << "\n";
    std::cout << "Codigo Barra : " << codigoBarra << "\n";
    std::cout << "Categoria    : " << categoria << "\n";
    std::cout << "Caducidad    : " << fechaCaducidad << "\n";
    std::cout << "Marca        : " << marca << "\n";
    // fixed y setprecision para mostrar el precio con 2 decimales
    std::cout << "Precio       : Q" << std::fixed
            << std::setprecision(2) << precio << "\n";
    std::cout << "Stock        : " << stock << " unidades\n";
    std::cout << "------------------------------\n";
}

// Comparamos por nombre en minúsculas para que sea case-insensitive
// (útil cuando el AVL necesita ordenar alfabéticamente)
bool Producto::operator<(const Producto &otro) const {
    return nombre < otro.nombre;
}

bool Producto::operator==(const Producto &otro) const {
    // Dos productos son iguales si tienen el mismo código de barra
    // (que es la clave única del sistema)
    return codigoBarra == otro.codigoBarra;
}
