# Sesión 7 :

ejercicio1: ejercicio1.c grafos.o cola.o monticulo.o
	gcc -g ejercicio1.c grafos.o cola.o monticulo.o -o ejercicio1
ejercicio1y2: ejercicio1y2.c grafos.o cola.o monticulo.o
	gcc -g ejercicio1y2.c grafos.o cola.o monticulo.o -o ejercicio1y2
ejercicio3: ejercicio3.c grafos.o cola.o monticulo.o
	gcc -g ejercicio3.c grafos.o cola.o monticulo.o -o ejercicio3
ejercicio4: ejercicio4.c grafos.o cola.o monticulo.o conjuntos.o pila.o
	gcc -g ejercicio4.c grafos.o cola.o monticulo.o conjuntos.o pila.o -o ejercicio4
grafos.o: grafos.c grafos.h
	gcc -g -c grafos.c
cola.o: cola.c cola.h
	gcc -g -c cola.c
conjuntos.o: conjuntos.c conjuntos.h
	gcc -g -c conjuntos.c
monticulo.o: monticulo.c monticulo.h
	gcc -g -c monticulo.c
pila.o: pila.c pila.h
	gcc -g -c pila.c

