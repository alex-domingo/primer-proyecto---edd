#include <iostream>
#include <limits>
#include <string>
#include "Catalogo.h"
#include "CargadorCSV.h"
#include "MedidorRendimiento.h"
#include "VisualizadorDot.h"

/*
 * main.cpp
 * ---------
 * Punto de entrada del sistema de gestion de catalogo de supermercado.
 *
 * El sistema arranca vacio. El usuario elige cuando cargar el CSV.
 * Ninguna entrada invalida cierra el programa — siempre se vuelve al menu.
 *
 * Opciones del menu:
 *   1. Cargar productos desde CSV
 *   2. Agregar producto manualmente
 *   3. Eliminar producto
 *   4. Buscar por nombre          [AVL - O(log n)]
 *   5. Buscar por categoria       [Arbol B+ - O(log n + k)]
 *   6. Buscar por rango de fecha  [Arbol B  - O(log n + k)]
 *   7. Listar todos (A-Z)         [AVL in-order]
 *   8. Listar por orden insercion [Lista simple]
 *   9. Listar orden alfabetico    [Lista ordenada]
 *  10. Medicion de rendimiento
 *  11. Generar visualizaciones (.dot)
 *   0. Salir
 */

// ============================================================
// Helpers de entrada — robustos ante cualquier input
// ============================================================

// Limpia lo que quede pendiente en el buffer de cin
void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Lee una linea completa de texto (acepta espacios)
std::string leerLinea(const std::string &etiqueta) {
    std::string valor;
    std::cout << etiqueta;
    std::getline(std::cin, valor);
    return valor;
}

/*
 * Lee un numero decimal no negativo.
 * Si el usuario ingresa texto o un numero negativo, repite la solicitud.
 * Nunca lanza excepcion ni cierra el programa.
 */
double leerDouble(const std::string &etiqueta) {
    double valor = 0.0;
    while (true) {
        std::cout << etiqueta;
        if (std::cin >> valor && valor >= 0.0) {
            limpiarBuffer();
            return valor;
        }
        std::cout << "  [!] Ingresa un numero valido (>= 0). Ejemplo: 12.50\n";
        std::cin.clear();
        limpiarBuffer();
    }
}

/*
 * Lee un entero no negativo.
 * Misma logica de reintento que leerDouble.
 */
int leerInt(const std::string &etiqueta) {
    int valor = 0;
    while (true) {
        std::cout << etiqueta;
        if (std::cin >> valor && valor >= 0) {
            limpiarBuffer();
            return valor;
        }
        std::cout << "  [!] Ingresa un numero entero valido (>= 0). Ejemplo: 100\n";
        std::cin.clear();
        limpiarBuffer();
    }
}

// ============================================================
// Funciones del menu
// ============================================================

/*
 * Opcion 1: Carga el catalogo desde un archivo CSV.
 * El usuario puede ingresar la ruta que quiera, o dejar en blanco
 * para usar la ruta por defecto (data/productos.csv).
 */
void menuCargarCSV(Catalogo &catalogo) {
    std::cout << "\n--- Cargar productos desde CSV ---\n";

    if (!catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo ya tiene " << catalogo.contarProductos()
                << " productos.\n";
        std::cout << "  Cargar otro CSV agregara los productos nuevos (los duplicados se omiten).\n";
        std::cout << "  Continuar? (s/n): ";
        std::string conf;
        std::getline(std::cin, conf);
        if (conf != "s" && conf != "S") {
            std::cout << "  Operacion cancelada.\n";
            return;
        }
    }

    std::cout << "  Ruta por defecto: data/productos.csv\n";
    std::string ruta = leerLinea("  Ruta del archivo (Enter para usar la default): ");

    // Si el usuario presiono Enter sin escribir nada, usamos la ruta default
    if (ruta.empty()) {
        ruta = "data/productos.csv";
    }

    std::cout << "\n";
    CargadorCSV cargador("data/errors.log");
    int cargados = cargador.cargar(ruta, catalogo);

    if (cargados > 0) {
        std::cout << "\n[OK] " << cargados << " productos cargados."
                << " Total en catalogo: " << catalogo.contarProductos() << "\n";
    } else {
        std::cout << "\n[!] No se cargo ningun producto. Revisa la ruta y el archivo.\n";
    }
}

/*
 * Opcion 2: Agrega un producto ingresando sus datos manualmente.
 * Valida campos obligatorios y formatos antes de insertar.
 */
void menuAgregarProducto(Catalogo &catalogo) {
    std::cout << "\n--- Agregar producto manualmente ---\n";

    std::string nombre = leerLinea("  Nombre                      : ");
    std::string codigo = leerLinea("  Codigo de barra             : ");
    std::string categoria = leerLinea("  Categoria                   : ");
    std::string fecha = leerLinea("  Fecha caducidad (YYYY-MM-DD): ");
    std::string marca = leerLinea("  Marca                       : ");
    double precio = leerDouble("  Precio (Q)                  : ");
    int stock = leerInt("  Stock (unidades)            : ");

    if (nombre.empty() || codigo.empty() || categoria.empty() ||
        fecha.empty() || marca.empty()) {
        std::cout << "\n[!] Todos los campos de texto son obligatorios. Operacion cancelada.\n";
        return;
    }

    Producto p(nombre, codigo, categoria, fecha, marca, precio, stock);

    if (catalogo.agregarProducto(p)) {
        std::cout << "\n[OK] Producto '" << nombre << "' agregado.\n";
        std::cout << "     Total en catalogo: " << catalogo.contarProductos() << " productos.\n";
    }
    // Si falla, el Catalogo ya imprime el motivo (duplicado, nombre repetido, etc.)
}

/*
 * Opcion 3: Elimina un producto buscandolo primero por nombre.
 * Muestra los datos y pide confirmacion antes de borrar.
 */
void menuEliminarProducto(Catalogo &catalogo) {
    std::cout << "\n--- Eliminar producto ---\n";

    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio. No hay productos que eliminar.\n";
        return;
    }

    std::string nombre = leerLinea("  Nombre del producto a eliminar: ");
    if (nombre.empty()) {
        std::cout << "  [!] El nombre no puede estar vacio.\n";
        return;
    }

    Producto *encontrado = catalogo.buscarPorNombre(nombre);
    if (encontrado == nullptr) return; // buscarPorNombre ya imprime "no encontrado"

    std::cout << "\n  Producto encontrado:\n";
    encontrado->mostrar();
    std::cout << "  Confirmar eliminacion (s/n): ";
    std::string conf;
    std::getline(std::cin, conf);

    if (conf != "s" && conf != "S") {
        std::cout << "  Operacion cancelada.\n";
        return;
    }

    // Guardamos los datos antes de llamar a eliminar porque el puntero
    // puede quedar invalido una vez que la estructura lo libera
    std::string nomb = encontrado->nombre;
    std::string cod = encontrado->codigoBarra;
    std::string cat = encontrado->categoria;
    std::string fec = encontrado->fechaCaducidad;

    if (catalogo.eliminarProducto(nomb, cod, cat, fec)) {
        std::cout << "[OK] Producto '" << nomb << "' eliminado.\n";
        std::cout << "     Total en catalogo: " << catalogo.contarProductos() << " productos.\n";
    }
}

/*
 * Opcion 4: Busca un producto por nombre exacto usando el AVL — O(log n).
 */
void menuBuscarPorNombre(Catalogo &catalogo) {
    std::cout << "\n--- Buscar por nombre [AVL - O(log n)] ---\n";

    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio.\n";
        return;
    }

    std::string nombre = leerLinea("  Nombre a buscar: ");
    if (nombre.empty()) {
        std::cout << "  [!] El nombre no puede estar vacio.\n";
        return;
    }

    std::cout << "\n";
    Producto *resultado = catalogo.buscarPorNombre(nombre);
    if (resultado != nullptr) resultado->mostrar();
}

/*
 * Opcion 5: Busca todos los productos de una categoria — O(log n + k).
 * El arbol B+ es ideal para esto: las hojas estan enlazadas y podemos
 * recorrer todos los de la misma categoria sin subir el arbol.
 */
void menuBuscarPorCategoria(Catalogo &catalogo) {
    std::cout << "\n--- Buscar por categoria [Arbol B+ - O(log n + k)] ---\n";

    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio.\n";
        return;
    }

    std::string cat = leerLinea("  Categoria a buscar: ");
    if (cat.empty()) {
        std::cout << "  [!] La categoria no puede estar vacia.\n";
        return;
    }

    std::cout << "\nProductos de la categoria '" << cat << "':\n";
    std::cout << "--------------------------------------------\n";
    catalogo.buscarPorCategoria(cat);
}

/*
 * Opcion 6: Busca productos por rango de fecha de caducidad — O(log n + k).
 * El arbol B esta indexado por fecha, por eso soporta este tipo de consulta
 * sin tener que recorrer todos los productos.
 */
void menuBuscarPorRangoFecha(Catalogo &catalogo) {
    std::cout << "\n--- Buscar por rango de fecha [Arbol B - O(log n + k)] ---\n";

    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio.\n";
        return;
    }

    std::cout << "  Formato de fecha: YYYY-MM-DD\n";
    std::string ini = leerLinea("  Fecha inicio: ");
    std::string fin = leerLinea("  Fecha fin   : ");

    if (ini.empty() || fin.empty()) {
        std::cout << "  [!] Ambas fechas son obligatorias.\n";
        return;
    }
    if (ini > fin) {
        std::cout << "  [!] La fecha de inicio no puede ser mayor que la fecha fin.\n";
        return;
    }

    std::cout << "\n";
    catalogo.buscarPorRangoFecha(ini, fin);
}

/*
 * Opcion 7: Lista todos los productos en orden A-Z via AVL in-order.
 */
void menuListarPorNombre(Catalogo &catalogo) {
    std::cout << "\n--- Listado A-Z [AVL in-order] ---\n";
    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio.\n";
        return;
    }
    std::cout << "Total: " << catalogo.contarProductos() << " productos\n\n";
    catalogo.listarPorNombre();
}

/*
 * Opcion 8: Lista en orden de insercion via lista simple.
 * Como insertamos al frente, el primer elemento de la lista es el
 * ultimo que se agrego (orden inverso al CSV).
 */
void menuListarSimple(Catalogo &catalogo) {
    std::cout << "\n--- Listado por orden de insercion [Lista simple] ---\n";
    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio.\n";
        return;
    }
    std::cout << "Total: " << catalogo.contarProductos() << " productos\n\n";
    catalogo.listarSimple();
}

/*
 * Opcion 9: Lista en orden alfabetico via lista ordenada.
 * La lista mantiene el orden en cada insercion, asi que listar
 * es simplemente recorrerla de cabeza a cola.
 */
void menuListarOrdenado(Catalogo &catalogo) {
    std::cout << "\n--- Listado alfabetico [Lista ordenada] ---\n";
    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio.\n";
        return;
    }
    std::cout << "Total: " << catalogo.contarProductos() << " productos\n\n";
    catalogo.listarOrdenado();
}

/*
 * Opcion 10: Compara los tiempos de busqueda entre las tres estructuras.
 * Metodologia del enunciado: M=5 bloques x N=20 busquedas, promedio en us.
 */
void menuBenchmark(Catalogo &catalogo) {
    std::cout << "\n--- Medicion de rendimiento ---\n";

    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio. Carga el CSV primero (opcion 1).\n";
        return;
    }
    if (catalogo.contarProductos() < 20) {
        std::cout << "  [!] Se necesitan al menos 20 productos para el benchmark.\n";
        std::cout << "      Actualmente hay " << catalogo.contarProductos() << ".\n";
        return;
    }

    const int TOTAL = 20;
    std::string nombres[TOTAL];

    // Elegimos los nombres segun el CSV que se haya cargado
    if (catalogo.contarProductos() <= 25) {
        // Nombres del CSV de 25 productos (muestra25.csv)
        std::string n[] = {
            "Aceite de Oliva", "Agua Pura", "Arroz Blanco",
            "Atun en Aceite", "Banano", "Cafe Molido",
            "Cerveza Artesanal", "Chocolate Negro", "Detergente Liquido",
            "Frijoles Negros", "Galletas Saladas", "Harina de Trigo",
            "Jugo de Naranja", "Leche Entera", "Maiz Amarillo",
            "Mantequilla", "Oregano", "Pizza Congelada",
            "Queso Fresco", "Zanahoria"
        };
        for (int i = 0; i < TOTAL; i++) nombres[i] = n[i];
    } else {
        // Nombres del CSV de 1050 productos (productos.csv)
        std::string n[] = {
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
        for (int i = 0; i < TOTAL; i++) nombres[i] = n[i];
    }

    MedidorRendimiento medidor(
        catalogo.obtenerListaSimple(),
        catalogo.obtenerListaOrdenada(),
        catalogo.obtenerArbolAVL()
    );
    medidor.ejecutar(nombres, TOTAL);
}

/*
 * Opcion 11: Genera los archivos .dot en output/ para visualizar con Graphviz.
 */
void menuVisualizarArboles(Catalogo &catalogo) {
    std::cout << "\n--- Generar visualizaciones Graphviz (.dot) ---\n";

    if (catalogo.estaVacio()) {
        std::cout << "  [!] El catalogo esta vacio. Carga el CSV primero (opcion 1).\n";
        return;
    }

    VisualizadorDot viz("output");
    viz.generarTodos(
        catalogo.obtenerArbolAVL(),
        catalogo.obtenerArbolB(),
        catalogo.obtenerArbolBPlus()
    );
}

// ============================================================
// Menu principal
// ============================================================

void imprimirMenu(int totalProductos) {
    std::cout << "\n==========================================\n";
    std::cout << "   CATALOGO DE PRODUCTOS - SUPERMERCADO  \n";
    std::cout << "  Productos cargados: " << totalProductos << "\n";
    std::cout << "==========================================\n";
    std::cout << "  DATOS\n";
    std::cout << "   1. Cargar productos desde CSV\n";
    std::cout << "   2. Agregar producto manualmente\n";
    std::cout << "   3. Eliminar producto\n";
    std::cout << "------------------------------------------\n";
    std::cout << "  BUSQUEDAS\n";
    std::cout << "   4. Buscar por nombre          [AVL]\n";
    std::cout << "   5. Buscar por categoria       [Arbol B+]\n";
    std::cout << "   6. Buscar por rango de fecha  [Arbol B]\n";
    std::cout << "------------------------------------------\n";
    std::cout << "  LISTADOS\n";
    std::cout << "   7. Listar todos (A-Z)\n";
    std::cout << "   8. Listar por orden de insercion\n";
    std::cout << "   9. Listar por orden alfabetico\n";
    std::cout << "------------------------------------------\n";
    std::cout << "  HERRAMIENTAS\n";
    std::cout << "  10. Medicion de rendimiento\n";
    std::cout << "  11. Generar visualizaciones (.dot)\n";
    std::cout << "------------------------------------------\n";
    std::cout << "   0. Salir\n";
    std::cout << "==========================================\n";
    std::cout << "  Opcion: ";
}

// ============================================================
// main
// ============================================================

int main() {
    std::cout << "==========================================\n";
    std::cout << "   CATALOGO DE PRODUCTOS - SUPERMERCADO  \n";
    std::cout << "         Curso Estructura de Datos       \n";
    std::cout << "==========================================\n";
    std::cout << "  Sistema iniciado. Catalogo vacio.\n";
    std::cout << "  Usa la opcion 1 para cargar productos.\n";

    Catalogo catalogo;

    /*
     * Bucle principal del menu.
     * - Se repite hasta que el usuario ingrese 0.
     * - Leemos SIEMPRE con getline para capturar la linea completa.
     *   Luego intentamos convertirla a entero con stoi.
     * - Cualquier entrada no numerica (letras, simbolos, texto) o fuera
     *   de rango muestra un aviso y vuelve al menu.
     */
    int opcion = -1;
    while (opcion != 0) {
        imprimirMenu(catalogo.contarProductos());

        // Leemos la linea completa — nunca falla independientemente de lo que escriba el usuario
        std::string lineaOpcion;
        std::getline(std::cin, lineaOpcion);

        // Intentamos convertir a entero
        try {
            // stoi lanza excepcion si la cadena no empieza con un digito
            size_t pos = 0;
            opcion = std::stoi(lineaOpcion, &pos);
            // Si quedan caracteres despues del numero (ej: "5abc"), lo rechazamos
            if (pos != lineaOpcion.size()) {
                std::cout << "\n  [!] Opcion invalida. Ingresa solo un numero del 0 al 11.\n";
                opcion = -1;
                continue;
            }
        } catch (...) {
            // Cualquier error de conversion (letras, simbolos, vacio, etc.)
            std::cout << "\n  [!] Opcion invalida. Ingresa un numero del 0 al 11.\n";
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1: menuCargarCSV(catalogo);
                break;
            case 2: menuAgregarProducto(catalogo);
                break;
            case 3: menuEliminarProducto(catalogo);
                break;
            case 4: menuBuscarPorNombre(catalogo);
                break;
            case 5: menuBuscarPorCategoria(catalogo);
                break;
            case 6: menuBuscarPorRangoFecha(catalogo);
                break;
            case 7: menuListarPorNombre(catalogo);
                break;
            case 8: menuListarSimple(catalogo);
                break;
            case 9: menuListarOrdenado(catalogo);
                break;
            case 10: menuBenchmark(catalogo);
                break;
            case 11: menuVisualizarArboles(catalogo);
                break;
            case 0:
                std::cout << "\n[OK] Hasta pronto.\n\n";
                break;
            default:
                // Numero fuera de rango — volvemos al menu sin hacer nada
                std::cout << "\n  [!] Opcion invalida. Ingresa un numero del 0 al 11.\n";
        }
    }

    return 0;
}
