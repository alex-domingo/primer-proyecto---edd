#include <iostream>
#include "catalogo.h"

/*
 * main.cpp
 * --------
 * Punto de entrada del programa.
 * Por ahora solo verifica que todo compile correctamente
 * y muestra un menú básico como prueba de humo.
 *
 * El menú completo se implementa en la fase 10.
 */

int main() {
    std::cout << "=========================================\n";
    std::cout << "  Catalogo de Productos - Supermercado  \n";
    std::cout << "=========================================\n\n";

    // Creamos el catálogo — el orquestador central del sistema
    Catalogo catalogo;

    // Prueba rápida para verificar que la clase Producto funciona
    Producto p("Leche Entera", "7501234567890", "Lacteos",
               "2025-12-31", "Dos Pinos", 12.50, 100);

    std::cout << "\nProducto de prueba:\n";
    p.mostrar();

    // Intentamos agregar al catálogo (todavía no implementado)
    catalogo.agregarProducto(p);

    std::cout << "\nFase 0 completada — estructura base lista.\n";
    return 0;
}
