#include <iostream>
#include "Catalogo.h"

/*
 * main.cpp — prueba de la Fase 5
 * --------------------------------
 * Verificamos que el Catálogo:
 *   1. Inserta en las 5 estructuras simultáneamente
 *   2. Rechaza duplicados de código de barra
 *   3. Hace rollback si el AVL rechaza un nombre duplicado
 *   4. Elimina de todas las estructuras a la vez
 *   5. Cada búsqueda va a la estructura correcta
 */

int main() {
    std::cout << "=========================================\n";
    std::cout << "      Fase 5 - Prueba del Catalogo      \n";
    std::cout << "=========================================\n\n";

    Catalogo catalogo;

    // -- Productos de prueba --
    Producto p1("Leche Entera", "1000000000001", "Lacteos", "2026-06-01", "Dos Pinos", 12.50, 50);
    Producto p2("Yogur Natural", "1000000000002", "Lacteos", "2026-05-15", "Dos Pinos", 18.50, 30);
    Producto p3("Arroz Blanco", "1000000000003", "Granos", "2027-01-01", "Gallo", 8.75, 200);
    Producto p4("Frijoles Negros", "1000000000004", "Granos", "2027-03-20", "Ducal", 6.25, 150);
    Producto p5("Cafe Molido", "1000000000005", "Bebidas", "2027-06-01", "Cafe Britt", 22.00, 60);
    Producto p6("Pan de Molde", "1000000000006", "Panaderia", "2026-03-10", "Bimbo", 15.00, 80);

    // =============================================
    // PRUEBA 1: Inserción correcta en las 5 estructuras
    // =============================================
    std::cout << "--- Insertando 6 productos validos ---\n";
    std::cout << "p1: " << (catalogo.agregarProducto(p1) ? "OK" : "Fallo") << "\n";
    std::cout << "p2: " << (catalogo.agregarProducto(p2) ? "OK" : "Fallo") << "\n";
    std::cout << "p3: " << (catalogo.agregarProducto(p3) ? "OK" : "Fallo") << "\n";
    std::cout << "p4: " << (catalogo.agregarProducto(p4) ? "OK" : "Fallo") << "\n";
    std::cout << "p5: " << (catalogo.agregarProducto(p5) ? "OK" : "Fallo") << "\n";
    std::cout << "p6: " << (catalogo.agregarProducto(p6) ? "OK" : "Fallo") << "\n";
    std::cout << "Total: " << catalogo.contarProductos() << " productos\n\n";

    // =============================================
    // PRUEBA 2: Rechazar código de barra duplicado
    // =============================================
    std::cout << "--- Insertando codigo de barra duplicado ---\n";
    Producto dup("Leche Descremada", "1000000000001", "Lacteos", "2026-07-01", "Dos Pinos", 11.00, 40);
    std::cout << "Resultado: " << (catalogo.agregarProducto(dup) ? "OK" : "Rechazado") << "\n";
    std::cout << "Total sigue siendo: " << catalogo.contarProductos() << "\n\n";

    // =============================================
    // PRUEBA 3: Rollback por nombre duplicado en AVL
    // =============================================
    std::cout << "--- Insertando nombre duplicado (rollback AVL) ---\n";
    Producto dupNombre("Leche Entera", "9999999999999", "Lacteos", "2026-08-01", "Dos Pinos", 13.00, 25);
    std::cout << "Resultado: " << (catalogo.agregarProducto(dupNombre) ? "OK" : "Rechazado con rollback") << "\n";
    std::cout << "Total sigue siendo: " << catalogo.contarProductos() << "\n\n";

    // =============================================
    // PRUEBA 4: Validación de datos inválidos
    // =============================================
    std::cout << "--- Insertando datos invalidos ---\n";
    Producto invalido("Atun", "8888888888888", "Conservas", "2026-01-01", "Sardimar", -5.0, 10);
    std::cout << "Precio negativo: " << (catalogo.agregarProducto(invalido) ? "OK" : "Rechazado") << "\n\n";

    // =============================================
    // PRUEBA 5: Búsquedas usando cada estructura
    // =============================================
    std::cout << "--- Busqueda por nombre (AVL) ---\n";
    Producto *enc = catalogo.buscarPorNombre("Cafe Molido");
    if (enc) enc->mostrar();

    std::cout << "\n--- Busqueda por categoria 'Lacteos' (B+) ---\n";
    catalogo.buscarPorCategoria("Lacteos");

    std::cout << "\n--- Busqueda por rango de fecha (B) ---\n";
    catalogo.buscarPorRangoFecha("2026-01-01", "2026-12-31");

    // =============================================
    // PRUEBA 6: Listado por nombre (AVL in-order)
    // =============================================
    std::cout << "\n--- Listado por nombre A-Z ---\n";
    catalogo.listarPorNombre();

    // =============================================
    // PRUEBA 7: Eliminación propagada
    // =============================================
    std::cout << "\n--- Eliminando 'Yogur Natural' de todas las estructuras ---\n";
    bool elim = catalogo.eliminarProducto("Yogur Natural", "1000000000002",
                                          "Lacteos", "2026-05-15");
    std::cout << "Eliminacion: " << (elim ? "OK" : "Fallo") << "\n";
    std::cout << "Total ahora: " << catalogo.contarProductos() << "\n\n";

    std::cout << "--- Lacteos tras eliminacion ---\n";
    catalogo.buscarPorCategoria("Lacteos");

    std::cout << "\n--- Listado A-Z tras eliminacion ---\n";
    catalogo.listarPorNombre();

    // =============================================
    // PRUEBA 8: Eliminar inexistente
    // =============================================
    std::cout << "\n--- Eliminando producto inexistente ---\n";
    bool elimFail = catalogo.eliminarProducto("Mantequilla", "0000000000000",
                                              "Lacteos", "2026-01-01");
    std::cout << "Resultado: " << (elimFail ? "OK" : "No encontrado") << "\n";

    std::cout << "\nFase 5 completada correctamente.\n";
    return 0;
}
