# Gestión de Catálogo de Productos de Supermercado

Curso de Estructura de Datos  

---

## Estructura del proyecto

```
proyecto_edd/
├── include/        # Headers (.h) de todas las clases
├── src/            # Implementaciones (.cpp)
├── data/           # CSV de productos y archivo de errores
├── output/         # Archivos .dot e imágenes Graphviz generadas
├── docs/           # Diagramas de clase, TADs y reporte
├── main.cpp        # Punto de entrada — menú interactivo
├── Makefile        # Para compilar desde terminal
├── CMakeLists.txt  # Para compilar desde CLion
```

---

## Compilar y ejecutar

### Opción A — Desde CLion
Abrir el proyecto normalmente. CLion detecta el `CMakeLists.txt` automáticamente.  
**Importante:** configurar el Working Directory en `$PROJECT_DIR$` para que el programa encuentre la carpeta `data/`.  
Presionar el botón **Run** o usar `Shift+F10`.

### Opción B — Desde terminal (Windows / Linux)

**Requisitos:** tener `g++` instalado (MinGW en Windows, gcc en Linux).

```bash
# Compilar
make

# Compilar y ejecutar directamente
make run

# Limpiar archivos compilados
make clean
```

> **`make` no reconocido en Windows (PowerShell):**  
> MinGW instala el ejecutable como `mingw32-make.exe` en lugar de `make.exe`, por eso PowerShell no lo reconoce. El fix es permanente y solo se hace una vez:
>
> 1. Abre el Explorador de archivos y navega a `C:\MinGW\bin\` (o la carpeta donde instalaste MinGW).
> 2. Busca el archivo `mingw32-make.exe`.
> 3. Haz una **copia** de ese archivo en la misma carpeta.
> 4. Renombra la copia a `make.exe`.
> 5. Abre una nueva terminal y verifica con:
>     ```
>    make --version
>    ```
>    Deberías ver algo como `GNU Make 3.82.90 Built for i686-pc-mingw32`.  
>    Desde ese momento `make`, `make run` y `make clean` funcionan normalmente.

---

## Uso del sistema

Al iniciar, el programa muestra el menú principal con el catálogo vacío.  
Usar la **opción 1** para cargar productos desde el CSV antes de realizar cualquier operación.

```
==========================================
  CATALOGO DE PRODUCTOS - SUPERMERCADO
  Productos cargados: 0
==========================================
  DATOS
   1. Cargar productos desde CSV
   2. Agregar producto manualmente
   3. Eliminar producto
  BUSQUEDAS
   4. Buscar por nombre          [AVL]
   5. Buscar por categoria       [Arbol B+]
   6. Buscar por rango de fecha  [Arbol B]
  LISTADOS
   7. Listar todos (A-Z)
   8. Listar por orden de insercion
   9. Listar por orden alfabetico
  HERRAMIENTAS
  10. Medicion de rendimiento
  11. Generar visualizaciones (.dot)
   0. Salir
==========================================
```

---

## Estructuras de datos implementadas

| Estructura     | Clave              | Operaciones principales          | Complejidad     |
|----------------|--------------------|----------------------------------|-----------------|
| Lista simple   | —                  | Insertar al frente, listar       | O(1) inserción  |
| Lista ordenada | Nombre             | Insertar ordenado, buscar        | O(n) inserción  |
| Árbol AVL      | Nombre             | Buscar, insertar, eliminar, A-Z  | O(log n)        |
| Árbol B        | Fecha de caducidad | Buscar rango de fechas           | O(log n + k)    |
| Árbol B+       | Categoría          | Buscar por categoría             | O(log n + k)    |

> **Nota:** el proyecto no incluye Tabla Hash. Las cinco estructuras anteriores cubren todos los requerimientos del enunciado.

---

## Formato del CSV

```
"Nombre","CodigoBarra","Categoria","FechaCaducidad","Marca","Precio","Stock"
```

El archivo de productos debe colocarse en `data/esto-es-un-ejemplo.csv`.  

Los errores de validación durante la carga se registran en `data/errors.log`.

---

## Visualización de árboles

La opción 11 del menú genera archivos `.dot` en `output/` para el AVL, el Árbol B y el Árbol B+.  
Para convertirlos a imagen PNG se necesita [Graphviz](https://graphviz.org/) instalado y desde 
la raiz del proyecto en nuestra terminal ejecutar:

```bash
dot -Tpng output/avl.dot     -o output/avl.png
dot -Tpng output/arbolB.dot  -o output/arbolB.png
dot -Tpng output/arbolBP.dot -o output/arbolBP.png
```

---

## Manejo de errores

- Entradas inválidas en el menú (texto, símbolos, números fuera de rango) muestran un aviso y vuelven al menú sin cerrar el programa.
- El CSV tolera campos con comillas, precios decimales y detecta duplicados.
- Los productos con campos vacíos, precio negativo o stock no entero se omiten y se registran en `errors.log`.