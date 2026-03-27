# ============================================================
# Makefile para proyecto_edd
# Funciona en Windows (MinGW/g++) y Linux (g++)
# Uso:
#   make          -> compila todo
#   make clean    -> elimina archivos compilados
#   make run      -> compila y ejecuta
# ============================================================

# -- Detectar sistema operativo ------------------------------
ifeq ($(OS), Windows_NT)
    # En Windows usamos .exe y el comando del para borrar
    EXE     = proyecto_edd.exe
    RM      = del /Q /F
    RMDIR   = rmdir /S /Q
    MKDIR   = mkdir
    SEP     = \\
else
    # En Linux/macOS no hay extensión y usamos rm
    EXE     = proyecto_edd
    RM      = rm -f
    RMDIR   = rm -rf
    MKDIR   = mkdir -p
    SEP     = /
endif

# -- Compilador y flags --------------------------------------
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# -- Carpetas ------------------------------------------------
SRC_DIR = src
OBJ_DIR = obj

# -- Archivos fuente y objetos -------------------------------
# Tomamos todos los .cpp de src/ y main.cpp
SOURCES  = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
MAIN_OBJ = $(OBJ_DIR)/main.o

# ============================================================
# Regla principal: construir el ejecutable
# ============================================================
all: $(OBJ_DIR) $(EXE)

$(EXE): $(MAIN_OBJ) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo ">>> Compilacion exitosa: $(EXE)"

# Compilar main.cpp
$(MAIN_OBJ): main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar cada .cpp de src/ en su .o correspondiente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta obj si no existe
$(OBJ_DIR):
ifeq ($(OS), Windows_NT)
	if not exist $(OBJ_DIR) $(MKDIR) $(OBJ_DIR)
else
	$(MKDIR) $(OBJ_DIR)
endif

# ============================================================
# Regla run: compilar y ejecutar directamente
# ============================================================
run: all
	./$(EXE)

# ============================================================
# Regla clean: limpiar archivos generados
# ============================================================
clean:
ifeq ($(OS), Windows_NT)
	if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
	if exist $(EXE) $(RM) $(EXE)
else
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(EXE)
endif
	@echo ">>> Limpieza completa"

# Evitar conflictos con archivos que se llamen igual que las reglas
.PHONY: all run clean
