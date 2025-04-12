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


int insertar(tipoElementoMon x, Monticulo *m) {
	int i;		

	if(m->tamanno >= MAXIMO) {
		return -1;
	} else {
		m->tamanno++;
		m->elemento[m->tamanno] = x;
		filtradoAscendente(m, m->tamanno);
		return 0;
	}
}

int eliminarMinimo(Monticulo *m, tipoElementoMon *minimo) {

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

}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m) {

}

int esMonticulo(Monticulo m) {

}


/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan montículos */

void filtradoDescendente(Monticulo *m, int i) {
	int hijo;
	int finFiltrado = 0;
	tipoElementoMon aux;

	while(2*i <= m->tamanno && finFiltrado) {
		hijo = 2 * i;
		
		if(hijo != m->tamanno) {
			if(m->elemento[hijo+1].clave < m->elemento[hijo].clave) {
				hijo = hijo + 1; 
			}
		}

		if(m->elemento[hijo].clave < m->elemento[m->tamanno].clave) {
			m->elemento[i] = m->elemento[hijo];			
			/*aux = m->elemento[hijo];
			m->elemento[hijo] = m->elemento[i];
			m->elemento[hijo] = aux;*/
			i = hijo;
		} else {
			finFiltrado = 1;
		} 
	}

	m->elemento[i] = m->elemento[m->tamanno];
}

void filtradoAscendente(Monticulo *m, int i) {
	tipoElementoMon aux;
	
	while(i != 1 && m->elemento[i/2].clave > m->elemento[i].clave) {
		aux = m->elemento[i/2];
		m->elemento[i/2] = m->elemento[i];
		m->elemento[i] = aux;
		i = i / 2;
	}
}


/* Operación crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

void crearMonticulo(Monticulo *m) {

}
