# Variables
CC = gcc
CFLAGS = -Wall -Werror -Ilistas

# Objetos
OBJ = listas/lista.o pilas/pila.o colas/cola.o pruebaInsercion.o

# Compilación final
programa: $(OBJ)
	$(CC) $(CFLAGS) -o programa $(OBJ)

# Compilación de cada archivo
listas/lista.o: listas/lista.c listas/lista.h
	$(CC) $(CFLAGS) -c listas/lista.c -o listas/lista.o

pilas/pila.o: pilas/pila.c pilas/pila.h listas/lista.h
	$(CC) $(CFLAGS) -c pilas/pila.c -o pilas/pila.o

colas/cola.o: colas/cola.c colas/cola.h listas/lista.h
	$(CC) $(CFLAGS) -c colas/cola.c -o colas/cola.o

pruebaInsercion.o: pruebaInsercion.c pilas/pila.h listas/lista.h colas/cola.h
	$(CC) $(CFLAGS) -c pruebaInsercion.c -o pruebaInsercion.o


clean:
	-taskkill /F /IM programa.exe 2>nul || exit 0
	cmd /C del /Q listas\*.o pilas\*.o colas\*.o pruebaInsercion.o programa 2>nul
