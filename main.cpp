#include <iostream>
#include "ArbolB.h"

/*
 * main.cpp — prueba de la Fase 3
 * --------------------------------
 * Verificamos que el árbol B:
 *   1. Inserta correctamente y hace splits cuando es necesario
 *   2. Busca por fecha exacta
 *   3. Busca por rango de fechas (su operación estrella)
 *   4. Elimina correctamente
 *   5. Lista en orden cronológico
 */

int main() {
    std::cout << "=========================================\n";
    std::cout << "     Fase 3 - Prueba del Arbol B        \n";
    std::cout << "=========================================\n\n";

    ArbolB arbolB;

    // Productos con distintas fechas de caducidad para probar rangos
    Producto p1("Leche Entera", "1000000000001", "Lacteos", "2026-01-15", "Dos Pinos", 12.50, 50);
    Producto p2("Yogur Natural", "1000000000002", "Lacteos", "2026-02-28", "Dos Pinos", 18.50, 30);
    Producto p3("Pan de Molde", "1000000000003", "Panaderia", "2026-03-10", "Bimbo", 15.00, 80);
    Producto p4("Arroz Blanco", "1000000000004", "Granos", "2027-06-01", "Gallo", 8.75, 200);
    Producto p5("Frijoles Negros", "1000000000005", "Granos", "2027-08-20", "Ducal", 6.25, 150);
    Producto p6("Cafe Molido", "1000000000006", "Bebidas", "2027-11-30", "Cafe Britt", 22.00, 60);
    Producto p7("Azucar Blanca", "1000000000007", "Abarrotes", "2028-01-01", "Florida", 9.50, 300);
    Producto p8("Atun en Lata", "1000000000008", "Conservas", "2028-05-15", "Sardimar", 14.00, 120);
    Producto p9("Aceite Vegetal", "1000000000009", "Abarrotes", "2026-06-30", "Corona", 25.00, 90);

    // PRUEBA 1: Inserción (9 productos provocan varios splits en t=3)
    std::cout << "--- Insertando 9 productos ---\n";
    arbolB.insertar(p5);
    arbolB.insertar(p2);
    arbolB.insertar(p7);
    arbolB.insertar(p1);
    arbolB.insertar(p9);
    arbolB.insertar(p3);
    arbolB.insertar(p6);
    arbolB.insertar(p4);
    arbolB.insertar(p8);
    std::cout << "Productos en el arbol: " << arbolB.obtenerTamano() << "\n\n";

    // PRUEBA 2: Listado en orden cronológico
    std::cout << "--- Listado en orden cronologico ---\n";
    arbolB.listarEnOrden();

    // PRUEBA 3: Búsqueda exacta por fecha
    std::cout << "\n--- Busqueda exacta ---\n";
    Producto *enc = arbolB.buscar("2026-03-10");
    std::cout << "Buscando '2026-03-10': ";
    if (enc) {
        std::cout << "ENCONTRADO\n";
        enc->mostrar();
    } else { std::cout << "No encontrado\n"; }

    Producto *noEnc = arbolB.buscar("2025-12-31");
    std::cout << "Buscando '2025-12-31': "
            << (noEnc ? "Encontrado" : "No encontrado") << "\n\n";

    // PRUEBA 4: Búsqueda por rango (operación estrella del árbol B)
    std::cout << "--- Busqueda por rango [2026-01-01 al 2026-12-31] ---\n";
    arbolB.buscarRango("2026-01-01", "2026-12-31");

    std::cout << "\n--- Busqueda por rango [2027-06-01 al 2027-12-31] ---\n";
    arbolB.buscarRango("2027-06-01", "2027-12-31");

    // PRUEBA 5: Eliminación
    std::cout << "\n--- Eliminaciones ---\n";
    std::cout << "Eliminando '2026-01-15' (Leche Entera):  "
            << (arbolB.eliminar("2026-01-15") ? "OK" : "Fallo") << "\n";
    std::cout << "Eliminando '2028-01-01' (Azucar Blanca): "
            << (arbolB.eliminar("2028-01-01") ? "OK" : "Fallo") << "\n";
    std::cout << "Eliminando '2099-01-01' (no existe):     "
            << (arbolB.eliminar("2099-01-01") ? "OK" : "No encontrado") << "\n\n";

    std::cout << "Productos restantes: " << arbolB.obtenerTamano() << "\n\n";

    // PRUEBA 6: Listado final — debe seguir en orden cronológico
    std::cout << "--- Listado final (orden cronologico) ---\n";
    arbolB.listarEnOrden();

    std::cout << "\nFase 3 completada correctamente.\n";
    return 0;
}
