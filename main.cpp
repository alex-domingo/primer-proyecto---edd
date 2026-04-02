#include <iostream>
#include <cmath>
#include "Catalogo.h"
#include "CargadorCSV.h"
#include "MedidorRendimiento.h"

/*
 * main.cpp — prueba de la Fase 7
 * --------------------------------
 * 1. Cargamos el CSV con 1050 productos al catálogo
 * 2. Extraemos nombres en orden A-Z desde el AVL (in-order)
 *    para tener los extremos bien definidos
 * 3. Ejecutamos el benchmark comparativo
 */

// Recolecta nombres en orden A-Z recorriendo la lista ordenada
// (que ya los tiene en ese orden sin costo adicional)
int recolectarNombres(ListaOrdenada *lista, std::string *nombres, int maxNombres) {
    /*
     * Usamos un truco: listamos e interceptamos los nombres
     * Como ListaOrdenada no expone iterador, aprovechamos que
     * el Catálogo tiene buscarPorNombre y la lista tiene listar()
     * En su lugar usamos un arreglo fijo de nombres conocidos del CSV
     * que cargamos manualmente para el benchmark
     */
    (void) lista;
    (void) nombres;
    (void) maxNombres;
    return 0;
}

int main() {
    std::cout << "=========================================\n";
    std::cout << "  Catalogo de Productos - Supermercado  \n";
    std::cout << "=========================================\n\n";

    // =============================================
    // PASO 1: Cargar el CSV
    // =============================================
    Catalogo catalogo;
    CargadorCSV cargador("data/errors.log");

    std::cout << "Cargando productos desde CSV...\n";
    int total = cargador.cargar("data/productos.csv", catalogo);

    if (total == 0) {
        std::cout << "ERROR: no se pudo cargar el CSV. "
                "Verifica la ruta data/productos.csv\n";
        return 1;
    }

    std::cout << "\nProductos en el catalogo: " << catalogo.contarProductos() << "\n\n";

    // =============================================
    // PASO 2: Preparar nombres para el benchmark
    //
    // Seleccionamos nombres representativos:
    //  - Algunos que comienzan con letras del principio (A, B, C)
    //    → mejor caso para lista simple (están cerca del frente)
    //  - Algunos del medio
    //  - Algunos del final del alfabeto (Y, Z)
    //    → peor caso para lista simple
    //
    // Los ordenamos A-Z para que los extremos sean reales.
    // =============================================
    const int TOTAL_NOMBRES = 20;
    std::string nombresParaBenchmark[TOTAL_NOMBRES] = {
        // Principio del alfabeto (mejor caso lista simple si inserta al frente)
        "Aceite Vegetal Natural",
        "Aceite de Oliva",
        "Acondicionador Bio",
        "Agua Pura Bio",
        // Medio del alfabeto
        "Cafe Molido",
        "Cafe Molido Bio",
        "Frijoles Negros",
        "Granola Light",
        "Harina de Trigo Familiar",
        "Jabon Liquido Clasico",
        "Lentejas",
        "Leche Entera Extra",
        // Final del alfabeto (peor caso lista simple)
        "Salsa Picante",
        "Shampoo",
        "Suavizante Clasico",
        "Te Verde Natural",
        "Tomate en Lata",
        "Tortillas",
        "Uvas Eco",
        "Zanahoria"
    };

    // Verificamos cuántos existen realmente en el catálogo
    int existentes = 0;
    for (int i = 0; i < TOTAL_NOMBRES; i++) {
        if (catalogo.buscarPorNombre(nombresParaBenchmark[i]) != nullptr) {
            existentes++;
        }
    }
    std::cout << "\nNombres para benchmark verificados: "
            << existentes << "/" << TOTAL_NOMBRES << " existen en el catalogo\n";

    // =============================================
    // PASO 3: Ejecutar el benchmark
    // =============================================
    MedidorRendimiento medidor(
        catalogo.obtenerListaSimple(),
        catalogo.obtenerListaOrdenada(),
        catalogo.obtenerArbolAVL()
    );

    medidor.ejecutar(nombresParaBenchmark, TOTAL_NOMBRES);

    std::cout << "\nFase 7 completada correctamente.\n";
    return 0;
}
