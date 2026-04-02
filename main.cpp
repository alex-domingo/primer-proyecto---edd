#include <iostream>
#include <cmath>
#include "Catalogo.h"
#include "CargadorCSV.h"
#include "MedidorRendimiento.h"
#include "VisualizadorDot.h"

int main() {
    std::cout << "=========================================\n";
    std::cout << "  Catalogo de Productos - Supermercado  \n";
    std::cout << "=========================================\n\n";

    // PASO 1: Cargar el CSV
    Catalogo catalogo;
    CargadorCSV cargador("data/errors.log");
    int total = cargador.cargar("data/productos.csv", catalogo);

    if (total == 0) {
        std::cout << "ERROR: no se pudo cargar el CSV.\n";
        return 1;
    }
    std::cout << "\nProductos en el catalogo: " << catalogo.contarProductos() << "\n\n";

    // PASO 2: Medicion de rendimiento (Fase 7)
    const int TOTAL_NOMBRES = 20;
    std::string nombresParaBenchmark[TOTAL_NOMBRES] = {
        "Aceite Vegetal Natural", "Aceite de Oliva",
        "Acondicionador Bio", "Agua Pura Bio",
        "Cafe Molido", "Cafe Molido Bio",
        "Frijoles Negros", "Granola Light",
        "Harina de Trigo Familiar", "Jabon Liquido Clasico",
        "Lentejas", "Leche Entera Extra",
        "Salsa Picante", "Shampoo",
        "Suavizante Clasico", "Te Verde Natural",
        "Tomate en Lata", "Tortillas",
        "Uvas Eco", "Zanahoria"
    };

    MedidorRendimiento medidor(
        catalogo.obtenerListaSimple(),
        catalogo.obtenerListaOrdenada(),
        catalogo.obtenerArbolAVL()
    );
    medidor.ejecutar(nombresParaBenchmark, TOTAL_NOMBRES);

    // PASO 3: Visualizacion Graphviz (Fase 8)
    VisualizadorDot viz("output");
    viz.generarTodos(
        catalogo.obtenerArbolAVL(),
        catalogo.obtenerArbolB(),
        catalogo.obtenerArbolBPlus()
    );

    std::cout << "\nFases 7 y 8 completadas correctamente.\n";
    return 0;
}
