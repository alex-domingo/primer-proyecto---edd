#include <iostream>
#include "ListaSimple.h"
#include "ListaOrdenada.h"

/*
 * main.cpp — prueba de la Fase 1
 * --------------------------------
 * Probamos que ambas listas funcionen correctamente:
 * insertar, buscar y eliminar. Luego comparamos
 * cómo quedan ordenadas vs desordenadas.
 */

int main() {
    std::cout << "=========================================\n";
    std::cout << "  Fase 1 - Prueba de listas enlazadas   \n";
    std::cout << "=========================================\n\n";

    // -- Productos de prueba --
    Producto p1("Leche Entera", "1000000000001", "Lacteos", "2026-06-01", "Dos Pinos", 12.50, 50);
    Producto p2("Arroz Blanco", "1000000000002", "Granos", "2027-01-01", "Gallo", 8.75, 200);
    Producto p3("Pan de Molde", "1000000000003", "Panaderia", "2026-04-10", "Bimbo", 15.00, 80);
    Producto p4("Yogur Natural", "1000000000004", "Lacteos", "2026-05-15", "Dos Pinos", 18.50, 30);
    Producto p5("Frijoles Negros", "1000000000005", "Granos", "2027-03-20", "Ducal", 6.25, 150);

    // =============================================
    // PRUEBA 1: Lista Simple (no ordenada)
    // =============================================
    std::cout << "--- Lista Simple (insercion al frente) ---\n\n";
    ListaSimple listaSimple;

    listaSimple.insertar(p1);
    listaSimple.insertar(p2);
    listaSimple.insertar(p3);
    listaSimple.insertar(p4);
    listaSimple.insertar(p5);

    std::cout << "Elementos insertados: " << listaSimple.obtenerTamano() << "\n\n";
    listaSimple.listar();

    // Búsqueda exitosa
    std::cout << "\nBuscando 'Arroz Blanco'...\n";
    Producto *encontrado = listaSimple.buscarPorNombre("Arroz Blanco");
    if (encontrado) {
        encontrado->mostrar();
    }

    // Búsqueda fallida
    std::cout << "Buscando 'Atun en Lata' (no existe)...\n";
    Producto *noExiste = listaSimple.buscarPorNombre("Atun en Lata");
    std::cout << (noExiste ? "Encontrado" : "No encontrado") << "\n\n";

    // Eliminación
    std::cout << "Eliminando codigo '1000000000003' (Pan de Molde)...\n";
    bool eliminado = listaSimple.eliminar("1000000000003");
    std::cout << (eliminado ? "Eliminado OK" : "No encontrado") << "\n";
    std::cout << "Elementos restantes: " << listaSimple.obtenerTamano() << "\n\n";

    // =============================================
    // PRUEBA 2: Lista Ordenada (por nombre)
    // =============================================
    std::cout << "--- Lista Ordenada (por nombre alfabetico) ---\n\n";
    ListaOrdenada listaOrdenada;

    // Insertamos en desorden a propósito para verificar que se ordena solo
    listaOrdenada.insertar(p3); // Pan de Molde
    listaOrdenada.insertar(p1); // Leche Entera
    listaOrdenada.insertar(p5); // Frijoles Negros
    listaOrdenada.insertar(p2); // Arroz Blanco
    listaOrdenada.insertar(p4); // Yogur Natural

    std::cout << "Elementos insertados: " << listaOrdenada.obtenerTamano() << "\n\n";
    std::cout << "Listado (debe salir A-Z):\n";
    listaOrdenada.listar();

    // Búsqueda con corte anticipado
    std::cout << "\nBuscando 'Frijoles Negros' (con corte anticipado)...\n";
    Producto *enc2 = listaOrdenada.buscarPorNombre("Frijoles Negros");
    if (enc2) {
        enc2->mostrar();
    }

    // Eliminación
    std::cout << "Eliminando 'Leche Entera' (codigo 1000000000001)...\n";
    bool elim2 = listaOrdenada.eliminar("1000000000001");
    std::cout << (elim2 ? "Eliminado OK" : "No encontrado") << "\n";
    std::cout << "Elementos restantes: " << listaOrdenada.obtenerTamano() << "\n\n";
    std::cout << "Listado tras eliminacion:\n";
    listaOrdenada.listar();

    std::cout << "\nFase 1 completada correctamente.\n";
    return 0;
}
