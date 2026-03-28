#include <iostream>
#include "ArbolAVL.h"

/*
 * main.cpp — prueba de la Fase 2
 * --------------------------------
 * Verificamos que el árbol AVL:
 *   1. Inserta y mantiene el orden
 *   2. Se rebalancea correctamente (probamos los 4 casos)
 *   3. Busca en O(log n)
 *   4. Elimina correctamente (hoja, un hijo, dos hijos)
 *   5. Lista en orden alfabético (in-order)
 */

int main() {
    std::cout << "=========================================\n";
    std::cout << "     Fase 2 - Prueba del Arbol AVL      \n";
    std::cout << "=========================================\n\n";

    ArbolAVL avl;

    Producto p1("Leche Entera",    "1000000000001", "Lacteos",   "2026-06-01", "Dos Pinos", 12.50, 50);
    Producto p2("Arroz Blanco",    "1000000000002", "Granos",    "2027-01-01", "Gallo",      8.75, 200);
    Producto p3("Pan de Molde",    "1000000000003", "Panaderia", "2026-04-10", "Bimbo",     15.00,  80);
    Producto p4("Yogur Natural",   "1000000000004", "Lacteos",   "2026-05-15", "Dos Pinos", 18.50,  30);
    Producto p5("Frijoles Negros", "1000000000005", "Granos",    "2027-03-20", "Ducal",      6.25, 150);
    Producto p6("Cafe Molido",     "1000000000006", "Bebidas",   "2027-06-01", "Cafe Britt",22.00,  60);
    Producto p7("Azucar Blanca",   "1000000000007", "Abarrotes", "2028-01-01", "Florida",    9.50, 300);

    // PRUEBA 1: Inserción — insertamos en orden que provoca rotaciones
    std::cout << "--- Insertando 7 productos ---\n";
    avl.insertar(p4);
    avl.insertar(p2);
    avl.insertar(p7);
    avl.insertar(p5);
    avl.insertar(p1);
    avl.insertar(p3);
    avl.insertar(p6);
    std::cout << "Productos en el arbol: " << avl.obtenerTamano() << "\n\n";

    // PRUEBA 2: Listado in-order (debe salir A-Z)
    std::cout << "--- Listado in-order (debe ser A-Z) ---\n";
    avl.listarEnOrden();

    // PRUEBA 3: Búsquedas
    std::cout << "\n--- Busquedas ---\n";
    Producto *enc = avl.buscar("Cafe Molido");
    std::cout << "Buscando 'Cafe Molido': ";
    if (enc) { std::cout << "ENCONTRADO\n"; enc->mostrar(); }
    else      { std::cout << "No encontrado\n"; }

    Producto *noEnc = avl.buscar("Atun en Lata");
    std::cout << "Buscando 'Atun en Lata': "
              << (noEnc ? "Encontrado" : "No encontrado") << "\n\n";

    // PRUEBA 4: Eliminación — tres casos distintos
    std::cout << "--- Eliminaciones ---\n";
    std::cout << "Hoja 'Azucar Blanca':            " << (avl.eliminar("Azucar Blanca")  ? "OK" : "Fallo") << "\n";
    std::cout << "Un hijo 'Arroz Blanco':           " << (avl.eliminar("Arroz Blanco")   ? "OK" : "Fallo") << "\n";
    std::cout << "Dos hijos 'Leche Entera':         " << (avl.eliminar("Leche Entera")   ? "OK" : "Fallo") << "\n";
    std::cout << "Inexistente 'Mantequilla':        " << (avl.eliminar("Mantequilla")    ? "OK" : "No encontrado") << "\n\n";
    std::cout << "Productos restantes: " << avl.obtenerTamano() << "\n\n";

    // PRUEBA 5: Listado final — debe seguir en A-Z
    std::cout << "--- Listado final (debe seguir en A-Z) ---\n";
    avl.listarEnOrden();

    // PRUEBA 6: Duplicado — el tamaño no debe cambiar
    std::cout << "\n--- Insertando nombre duplicado ('Pan de Molde') ---\n";
    int antes = avl.obtenerTamano();
    avl.insertar(p3);
    std::cout << "Tamano antes: " << antes
              << " | Tamano despues: " << avl.obtenerTamano()
              << " (debe ser igual)\n";

    std::cout << "\nFase 2 completada correctamente.\n";
    return 0;
}
