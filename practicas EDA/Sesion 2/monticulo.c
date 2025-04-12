#include <stdlib.h>
#include <stdio.h>
#include "monticulo.h"


/* Ejercicio 1 */

void iniciaMonticulo(Monticulo *m) {
	m->tamanno = 0;
	return;
}


int vacioMonticulo(Monticulo m) {
	if(m.tamanno == 0 )
		return 1;
	else 
		return 0;
}


int insertar(tipoElemento x, Monticulo *m) {
	int hueco;		

	if(m->tamanno >= MAXIMO) {
		return -1;
	} else {
		m->tamanno++;
		hueco = m->tamanno;
		
		// ESTO ES EL ALGORTIMO DEL FILTRADO ASCENDENTE
		while(m->elemento[hueco/2].clave > x.clave && hueco != 1) { // Si el padre del nuevo elemento es mayor que el nuevo elemento y el valor no es 1 (la raiz)
			m->elemento[hueco] = m->elemento[hueco/2]; // El valor del padre pasara a la posicion del hijo
			hueco = hueco / 2; // Se divide entre dos el valor de la posicion parar seguir el algoritmo al siguiente padre
		}
		
		// Se llegara aqui cuando el valor del padre sea menor que el valor que se quiere insertar 
		m->elemento[hueco] = x; // Se asigna el valor a su posicion correspondiente
	}
	
	return 0;
}

int eliminarMinimo(Monticulo *m, tipoElemento *minimo) {
	int hueco;
	tipoElemento ultimo;
	int finFiltrado = 0;
	int hijo;

	if(vacioMonticulo(*m)) {
		return -1;
	} else {
		*minimo = m->elemento[1];
		ultimo = m->elemento[m->tamanno];
		m->tamanno = m->tamanno - 1;
		hueco = 1;
		
		// ESTO ES EL ALGORTIMO DEL FILTRADO DESCENDENTE
		while(2*hueco <= m->tamanno && finFiltrado == 0) {
			hijo = 2 * hueco; // Hijo del elemento de arriba (En la primera ejecuccion sera el hijo de la raiz)
			
			if(hijo != m->tamanno) { // Si el hijo no es la posicion maxima
				if(m->elemento[hijo+1].clave < m->elemento[hijo].clave) { // Se compara si el otro hijo, es decir, el "hermano" de la variable hijo es menor que Èl 
					hijo = hijo + 1;  // Si es menor el hijo sera el hermano
				}
			}
	
			if(m->elemento[hijo].clave < ultimo.clave) { // Se compara el elemento hijo con el elemento al que se le elimino la posicion
				m->elemento[hueco] = m->elemento[hijo]; // Si el hijo es menor se se asigna la posicion que estaba vacia 
				hueco = hijo;
			} else {
				finFiltrado = 1; // Si el hijo es mayor se acaba el filtrado
			}
		}
		
		m->elemento[hueco] = ultimo; // Se le asigna al hueco el valor que se habia quedado sin posicion (ultimo)
		return 0;
	}
	
	
	// OTRA POSIBLE IMPLANTACION
	if(vacioMonticulo(*m)) {
		return -1;
	} else {
		*minimo = m->elemento[1];
		filtradoDescendente(m, 1);
		m->tamanno = m->tamanno - 1;
		return 0;
	}
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m) {
	if(pos <= 0 || pos > m->tamanno) {
		return;	
	} else {
		m->elemento[pos].clave = m->elemento[pos].clave - cantidad;
		filtradoAscendente(m, pos);
	}
}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m) {
	if(pos <= 0 || pos > m->tamanno) {
		return;	
	} else {
		m->elemento[pos].clave = m->elemento[pos].clave + cantidad;
		filtradoDescendente(m, pos);
	}
}

int esMonticulo(Monticulo m) {
	int i;

	for(i = m.tamanno; i > 1; i--){
		if(m.elemento[i/2].clave > m.elemento[i].clave) {
			return 0;
		}
	}

	return 1;
}


/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan mont√≠culos */

void filtradoDescendente(Monticulo *m, int i) {
	int hijo, hueco;
	int finFiltrado = 0;
	tipoElemento aux, ultimo;
	
	while(2*i <= m->tamanno && finFiltrado) {
		hijo = 2 * i; // Hijo del elemento de arriba (En la primera ejecuccion sera el hijo de la raiz)
		
		if(hijo != m->tamanno) { // Si el hijo no es la posicion maxima
			if(m->elemento[hijo+1].clave < m->elemento[hijo].clave) { // Se compara si el otro hijo, es decir, el "hermano" de la variable hijo es menor que Èl 
				hijo = hijo + 1; // Si es menor el hijo sera el hermano
			}
		}

		if(m->elemento[hijo].clave < m->elemento[m->tamanno].clave) { // Se compara el elemento hijo con el elemento al que se le elimino la posicion
			m->elemento[i] = m->elemento[hijo];			
			i = hijo;
		} else {
			finFiltrado = 1;
		} 
	}

	m->elemento[i] = m->elemento[m->tamanno];
	
	
	// OTRA OPCION
	
	ultimo = m->elemento[m->tamanno];
	hueco = 1;
	
	while(2*hueco <= m->tamanno && finFiltrado == 0) {
			hijo = 2 * hueco; // Hijo del elemento de arriba (En la primera ejecuccion sera el hijo de la raiz)
			
			if(hijo != m->tamanno) { // Si el hijo no es la posicion maxima
				if(m->elemento[hijo+1].clave < m->elemento[hijo].clave) { // Se compara si el otro hijo, es decir, el "hermano" de la variable hijo es menor que Èl 
					hijo = hijo + 1;  // Si es menor el hijo sera el hermano
				}
			}
	
			if(m->elemento[hijo].clave < ultimo.clave) { // Se compara el elemento hijo con el elemento al que se le elimino la posicion
				m->elemento[hueco] = m->elemento[hijo]; // Si el hijo es menor se se asigna la posicion que estaba vacia 
				hueco = hijo;
			} else {
				finFiltrado = 1; // Si el hijo es mayor se acaba el filtrado
			}
		}
		
		m->elemento[hueco] = ultimo; // Se le asigna al hueco el valor que se habia quedado sin posicion (ultimo)	
}

void filtradoAscendente(Monticulo *m, int i) {  // i es es valor del elemento que se quiere insertar
	int hueco;
	
	hueco = m->tamanno+1;
	
	while( m->elemento[hueco/2].clave > m->elemento[i].clave && hueco != 1) { // Si el padre del nuevo elemento es mayor que el nuevo elemento y el valor no es 1 (la raiz)
		m->elemento[hueco] = m->elemento[hueco/2]; // El valor del padre pasara a la posicion del hijo
		hueco = hueco / 2; // Se divide entre dos el valor de la posicion parar seguir el algoritmo al siguiente padre
	}
	
	// Se llegara aqui cuando el valor del padre sea menor que el valor que se quiere insertar 
	m->elemento[hueco] = m->elemento[i]; // Se asigna el valor a su posicion correspondiente
}


/* Operaci√≥n crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

void crearMonticulo(Monticulo *m) {
	int i, n;
	
	n = m->tamanno;
	for(i = n/2; i <= 1; i--) { // Para cada nodo interno se realiza el filtrado descendente
		filtradoDescendente(m,i);
	}
}


void heapsort(Monticulo *m) { 
  	int i, n;
  	tipoElemento aux;	


		
	crearMonticulo(m);
	n = m->tamanno;

    for(i = 1; i <= n; i++) {
  		eliminarMinimo(m, &aux);
  		m->elemento[m->tamanno+1] = aux;
  	}
  	
  	m->tamanno = n;

  }
