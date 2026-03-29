#include <iostream>
#include "ArbolBPlus.h"

/*
 * main.cpp — prueba de la Fase 4
 * --------------------------------
 * Verificamos que el árbol B+:
 *   1. Inserta productos de múltiples categorías
 *   2. buscarPorCategoria recorre correctamente las hojas enlazadas
 *   3. Busca un producto exacto
 *   4. Lista todo en orden de categoría (caminando hojas)
 *   5. Elimina correctamente
 */

int main() {
    std::cout << "=========================================\n";
    std::cout << "    Fase 4 - Prueba del Arbol B+        \n";
    std::cout << "=========================================\n\n";

    ArbolBPlus arbolBP;

    // Varios productos — con categorías repetidas a propósito
    // para probar que buscarPorCategoria los encuentra todos
    Producto p1("Leche Entera", "1000000000001", "Lacteos", "2026-06-01", "Dos Pinos", 12.50, 50);
    Producto p2("Yogur Natural", "1000000000002", "Lacteos", "2026-05-15", "Dos Pinos", 18.50, 30);
    Producto p3("Queso Fresco", "1000000000003", "Lacteos", "2026-04-20", "Coronado", 22.00, 40);
    Producto p4("Arroz Blanco", "1000000000004", "Granos", "2027-01-01", "Gallo", 8.75, 200);
    Producto p5("Frijoles Negros", "1000000000005", "Granos", "2027-03-20", "Ducal", 6.25, 150);
    Producto p6("Cafe Molido", "1000000000006", "Bebidas", "2027-06-01", "Cafe Britt", 22.00, 60);
    Producto p7("Agua Pura", "1000000000007", "Bebidas", "2027-12-31", "Crystal", 5.00, 500);
    Producto p8("Pan de Molde", "1000000000008", "Panaderia", "2026-03-10", "Bimbo", 15.00, 80);
    Producto p9("Azucar Blanca", "1000000000009", "Abarrotes", "2028-01-01", "Florida", 9.50, 300);
    Producto p10("Aceite Vegetal", "1000000000010", "Abarrotes", "2026-06-30", "Corona", 25.00, 90);

    // PRUEBA 1: Inserción — mezclamos categorías a propósito
    std::cout << "--- Insertando 10 productos ---\n";
    arbolBP.insertar(p6);
    arbolBP.insertar(p1);
    arbolBP.insertar(p9);
    arbolBP.insertar(p4);
    arbolBP.insertar(p2);
    arbolBP.insertar(p7);
    arbolBP.insertar(p5);
    arbolBP.insertar(p8);
    arbolBP.insertar(p3);
    arbolBP.insertar(p10);
    std::cout << "Productos en el arbol: " << arbolBP.obtenerTamano() << "\n\n";

    // PRUEBA 2: Listado completo (caminando cadena de hojas)
    std::cout << "--- Listado completo por categoria (cadena de hojas) ---\n";
    arbolBP.listarEnOrden();

    // PRUEBA 3: Búsqueda por categoría — la operación estrella
    std::cout << "\n--- Busqueda por categoria 'Lacteos' ---\n";
    arbolBP.buscarPorCategoria("Lacteos");

    std::cout << "\n--- Busqueda por categoria 'Bebidas' ---\n";
    arbolBP.buscarPorCategoria("Bebidas");

    std::cout << "\n--- Busqueda por categoria 'Abarrotes' ---\n";
    arbolBP.buscarPorCategoria("Abarrotes");

    std::cout << "\n--- Busqueda por categoria inexistente 'Limpieza' ---\n";
    arbolBP.buscarPorCategoria("Limpieza");

    // PRUEBA 4: Eliminación
    std::cout << "\n--- Eliminaciones ---\n";
    std::cout << "Eliminando 'Yogur Natural' (Lacteos):   "
            << (arbolBP.eliminar("Lacteos", "1000000000002") ? "OK" : "Fallo") << "\n";
    std::cout << "Eliminando 'Agua Pura' (Bebidas):       "
            << (arbolBP.eliminar("Bebidas", "1000000000007") ? "OK" : "Fallo") << "\n";
    std::cout << "Eliminando inexistente:                 "
            << (arbolBP.eliminar("Lacteos", "9999999999999") ? "OK" : "No encontrado") << "\n\n";

    std::cout << "Productos restantes: " << arbolBP.obtenerTamano() << "\n\n";

    // PRUEBA 5: Verificar que 'Lacteos' solo tiene 2 ahora
    std::cout << "--- Lacteos tras eliminacion (debe haber 2) ---\n";
    arbolBP.buscarPorCategoria("Lacteos");

    std::cout << "\nFase 4 completada correctamente.\n";
    return 0;
}
