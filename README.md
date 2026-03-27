# Gestión de Catálogo de Productos de Supermercado

Proyecto universitario — Curso de Estructura de Datos

---

## Estructura del proyecto

```
proyecto_edd/
├── include/        # Headers (.h) de todas las clases
├── src/            # Implementaciones (.cpp)
├── data/           # CSV de productos y archivo de errores
├── output/         # Archivos .dot e imágenes Graphviz generadas
├── docs/           # Diagramas de clase, TADs y reporte
├── main.cpp        # Punto de entrada
├── Makefile        # Para compilar desde terminal
└── CMakeLists.txt  # Para compilar desde CLion
```

---

## Compilar y ejecutar

### Opción A — Desde CLion
Abrir el proyecto normalmente. CLion detecta el `CMakeLists.txt` automáticamente.  
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

---

## Estructuras de datos implementadas

| Estructura     | Clave             | Estado     |
|----------------|-------------------|------------|
| Lista simple   | —                 | Pendiente  |
| Lista ordenada | Nombre            | Pendiente  |
| Árbol AVL      | Nombre            | Pendiente  |
| Tabla Hash     | Código de barra   | Pendiente  |
| Árbol B        | Fecha de caducidad| Pendiente  |
| Árbol B+       | Categoría         | Pendiente  |

---

## Formato del CSV

```
"Nombre","CodigoBarra","Categoria","FechaCaducidad","Marca","Precio","Stock"
```

El archivo debe colocarse en `data/productos.csv`.  
Los errores de carga se registran en `data/errors.log`.

---

## Visualización de árboles

El programa puede generar archivos `.dot` en la carpeta `output/`.  
Para convertirlos a imagen PNG se necesita tener instalado [Graphviz](https://graphviz.org/).

```bash
dot -Tpng output/avl.dot -o output/avl.png
```