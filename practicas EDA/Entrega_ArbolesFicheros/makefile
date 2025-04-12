pruebaEj1: pruebaEjercicio1.c ejercicio1.o
	gcc -g pruebaEjercicio1.c ejercicio1.o -o pruebaEj1
ejercicio1.o: ejercicio1.h ejercicio1.c
	gcc -g -c ejercicio1.c 
pruebaEj2: pruebaEjercicio2.c ejercicio2.o
	gcc -g pruebaEjercicio2.c ejercicio2.o -o pruebaEj2
ejercicio2.o: ejercicio2.h ejercicio2.c
	gcc -g -c ejercicio2.c 
clean:
	rm *.o
