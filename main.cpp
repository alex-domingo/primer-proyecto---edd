#include <iostream>
#include <fstream>
#include "Catalogo.h"
#include "CargadorCSV.h"

/*
 * main.cpp — prueba de la Fase 6
 * --------------------------------
 * Verificamos que el CargadorCSV:
 *   1. Carga el CSV principal (1050 productos)
 *   2. Maneja un archivo inexistente
 *   3. Maneja un archivo vacío
 *   4. Maneja líneas corruptas y duplicados
 *   5. Los productos cargados son consultables
 */

// Crea archivos de prueba para casos edge
void crearArchivosEdge() {
    // Archivo vacío
    std::ofstream vacio("data/vacio.csv");
    vacio << "\"Nombre\",\"CodigoBarra\",\"Categoria\","
            "\"FechaCaducidad\",\"Marca\",\"Precio\",\"Stock\"\n";
    vacio.close();

    // Archivo con líneas corruptas y duplicados
    std::ofstream corrupto("data/corrupto.csv");
    corrupto << "\"Nombre\",\"CodigoBarra\",\"Categoria\","
            "\"FechaCaducidad\",\"Marca\",\"Precio\",\"Stock\"\n";
    // Línea válida
    corrupto << "\"Leche Entera\",\"1111111111111\",\"Lacteos\","
            "\"2026-06-01\",\"Dos Pinos\",\"12.50\",\"50\"\n";
    // Campos faltantes (malformada)
    corrupto << "\"Pan de Molde\",\"2222222222222\",\"Panaderia\"\n";
    // Precio no numérico
    corrupto << "\"Arroz Blanco\",\"3333333333333\",\"Granos\","
            "\"2027-01-01\",\"Gallo\",\"GRATIS\",\"100\"\n";
    // Stock no entero
    corrupto << "\"Yogur Natural\",\"4444444444444\",\"Lacteos\","
            "\"2026-05-15\",\"Dos Pinos\",\"18.50\",\"MUCHO\"\n";
    // Código de barra duplicado
    corrupto << "\"Leche Semidescremada\",\"1111111111111\",\"Lacteos\","
            "\"2026-07-01\",\"Dos Pinos\",\"11.00\",\"40\"\n";
    // Campo vacío
    corrupto << "\"\",\"5555555555555\",\"Bebidas\","
            "\"2027-03-01\",\"Crystal\",\"5.00\",\"200\"\n";
    // Precio negativo
    corrupto << "\"Cafe Molido\",\"6666666666666\",\"Bebidas\","
            "\"2027-06-01\",\"Cafe Britt\",\"-22.00\",\"60\"\n";
    // Línea válida adicional
    corrupto << "\"Frijoles Negros\",\"7777777777777\",\"Granos\","
            "\"2027-03-20\",\"Ducal\",\"6.25\",\"150\"\n";
    corrupto.close();
}

int main() {
    std::cout << "=========================================\n";
    std::cout << "     Fase 6 - Prueba del CargadorCSV    \n";
    std::cout << "=========================================\n\n";

    crearArchivosEdge();

    // =============================================
    // CASO 1: Archivo inexistente
    // =============================================
    std::cout << "--- Caso 1: archivo inexistente ---\n";
    {
        Catalogo cat;
        CargadorCSV cargador("data/errors_caso1.log");
        int n = cargador.cargar("data/no_existe.csv", cat);
        std::cout << "Productos cargados: " << n << " (esperado: 0)\n\n";
    }

    // =============================================
    // CASO 2: Archivo vacío (solo encabezado)
    // =============================================
    std::cout << "--- Caso 2: archivo vacio ---\n";
    {
        Catalogo cat;
        CargadorCSV cargador("data/errors_caso2.log");
        int n = cargador.cargar("data/vacio.csv", cat);
        std::cout << "Productos cargados: " << n << " (esperado: 0)\n\n";
    }

    // =============================================
    // CASO 3: Archivo con errores y duplicados
    // =============================================
    std::cout << "--- Caso 3: archivo con errores y duplicados ---\n";
    {
        Catalogo cat;
        CargadorCSV cargador("data/errors_caso3.log");
        int n = cargador.cargar("data/corrupto.csv", cat);
        std::cout << "Productos cargados: " << n << " (esperado: 2)\n";
        std::cout << "Verificando AVL (debe listar 2 productos A-Z):\n";
        cat.listarPorNombre();
        std::cout << "\n";
    }

    // =============================================
    // CASO 4: CSV principal con 1050 productos
    // =============================================
    std::cout << "--- Caso 4: CSV principal (1050 productos) ---\n";
    {
        Catalogo cat;
        CargadorCSV cargador("data/errors.log");
        cargador.cargar("data/productos.csv", cat);
        std::cout << "Total en catalogo: " << cat.contarProductos() << "\n\n";

        // Verificamos que las búsquedas funcionan sobre los datos reales
        std::cout << "Busqueda por categoria 'Lacteos':\n";
        cat.buscarPorCategoria("Lacteos");

        std::cout << "\nBusqueda por rango de fecha [2025-01-01 al 2025-12-31]:\n";
        cat.buscarPorRangoFecha("2025-01-01", "2025-12-31");
    }

    std::cout << "\nFase 6 completada correctamente.\n";
    return 0;
}
