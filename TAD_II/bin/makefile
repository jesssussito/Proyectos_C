# Makefile para Enunciado 1 (secuencial) y Enunciado 2 (dispersión)

# Directorios
SRC_DIR := ../src
INC_DIR := ../include
OBJ_DIR := ../lib

# Flags comunes
CFLAGS       := -g -I$(INC_DIR)
ALUM_CFLAGS  := $(CFLAGS) -DALUM
ASIG_CFLAGS  := $(CFLAGS) -DASIG

# Asegurar que existe OBJ_DIR (PowerShell/CMD)
$(OBJ_DIR):
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

# Objetivos por defecto
all: genAlumnosH genAsignaturasH modAlumnoH modAsigH pruebaSecuencial

# --------------------------------------------------------
# Enunciado 1: Organización Secuencial
# --------------------------------------------------------
pruebaSecuencial: \
    $(OBJ_DIR)/secuencial.o \
    $(OBJ_DIR)/pruebaSecuencial.o \
    $(OBJ_DIR)/alumno.o \
    $(OBJ_DIR)/dispersionAl.o | $(OBJ_DIR)
	gcc $^ -o $@

$(OBJ_DIR)/secuencial.o: $(SRC_DIR)/secuencial.c \
                        $(INC_DIR)/secuencial.h \
                        $(INC_DIR)/alumno.h | $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/pruebaSecuencial.o: $(SRC_DIR)/pruebaSecuencial.c \
                              $(INC_DIR)/secuencial.h | $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

# --------------------------------------------------------
# Enunciado 2: Dispersión de alumnos y asignaturas
# --------------------------------------------------------

# genFicheroHash – Alumnos
genAlumnosH: $(OBJ_DIR)/genFicheroHashAlum.o \
             $(OBJ_DIR)/dispersionAl.o \
             $(OBJ_DIR)/alumno.o | $(OBJ_DIR)
	gcc $^ -o $@

$(OBJ_DIR)/genFicheroHashAlum.o: $(SRC_DIR)/genFicheroHash.c \
                                 $(INC_DIR)/dispersion.h \
                                 $(INC_DIR)/alumno.h | $(OBJ_DIR)
	gcc $(ALUM_CFLAGS) -c $< -o $@

# genFicheroHash – Asignaturas
genAsignaturasH: $(OBJ_DIR)/genFicheroHashAsig.o \
                 $(OBJ_DIR)/dispersionAs.o \
                 $(OBJ_DIR)/asignatura.o | $(OBJ_DIR)
	gcc $^ -o $@

$(OBJ_DIR)/genFicheroHashAsig.o: $(SRC_DIR)/genFicheroHash.c \
                                 $(INC_DIR)/dispersion.h \
                                 $(INC_DIR)/asignatura.h | $(OBJ_DIR)
	gcc $(ASIG_CFLAGS) -c $< -o $@

# modFicheroHash – Alumnos
modAlumnoH: $(OBJ_DIR)/modFicheroHashAlum.o \
            $(OBJ_DIR)/dispersionAl.o \
            $(OBJ_DIR)/alumno.o | $(OBJ_DIR)
	gcc $^ -o $@

$(OBJ_DIR)/modFicheroHashAlum.o: $(SRC_DIR)/modFicheroHash.c \
                                $(INC_DIR)/dispersion.h \
                                $(INC_DIR)/alumno.h | $(OBJ_DIR)
	gcc $(ALUM_CFLAGS) -c $< -o $@

# modFicheroHash – Asignaturas
modAsigH: $(OBJ_DIR)/modFicheroHashAsig.o \
           $(OBJ_DIR)/dispersionAs.o \
           $(OBJ_DIR)/asignatura.o | $(OBJ_DIR)
	gcc $^ -o $@

$(OBJ_DIR)/modFicheroHashAsig.o: $(SRC_DIR)/modFicheroHash.c \
                                $(INC_DIR)/dispersion.h \
                                $(INC_DIR)/asignatura.h | $(OBJ_DIR)
	gcc $(ASIG_CFLAGS) -c $< -o $@

# Objetos genéricos de dispersión
$(OBJ_DIR)/dispersionAl.o: $(SRC_DIR)/dispersion.c \
                          $(INC_DIR)/dispersion.h \
                          $(INC_DIR)/alumno.h | $(OBJ_DIR)
	gcc $(ALUM_CFLAGS) -c $< -o $@

$(OBJ_DIR)/dispersionAs.o: $(SRC_DIR)/dispersion.c \
                          $(INC_DIR)/dispersion.h \
                          $(INC_DIR)/asignatura.h | $(OBJ_DIR)
	gcc $(ASIG_CFLAGS) -c $< -o $@

# Objetos específicos de datos
$(OBJ_DIR)/alumno.o: $(SRC_DIR)/alumnos.c \
                    $(INC_DIR)/alumno.h | $(OBJ_DIR)
	gcc $(ALUM_CFLAGS) -c $< -o $@

$(OBJ_DIR)/asignatura.o: $(SRC_DIR)/asignatura.c \
                         $(INC_DIR)/asignatura.h | $(OBJ_DIR)
	gcc $(ASIG_CFLAGS) -c $< -o $@

# --------------------------------------------------------
.PHONY: clean
clean:
	if exist "$(OBJ_DIR)\*.o"       del /Q "$(OBJ_DIR)\*.o"
	if exist "genAlumnosH.exe"       del /Q "genAlumnosH.exe"
	if exist "genAsignaturasH.exe"   del /Q "genAsignaturasH.exe"
	if exist "modAlumnoH.exe"        del /Q "modAlumnoH.exe"
	if exist "modAsigH.exe"          del /Q "modAsigH.exe"
	if exist "pruebaSecuencial.exe"  del /Q "pruebaSecuencial.exe"
