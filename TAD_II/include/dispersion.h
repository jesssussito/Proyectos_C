#ifndef __DISPERSION_H
#define __DISPERSION_H

#include <stdio.h>
#include <string.h>

// 1) Selección de tipo según compilación
#if defined(ALUM)
  #include "alumno.h"       // Define: C, tAlumno, prototipos específicos
  typedef tAlumno tipoReg; // tipoReg es ahora tAlumno
#elif defined(ASIG)
  #include "asignatura.h"   // Define: C, tAsignatura, prototipos específicos
  typedef tAsignatura tipoReg; // tipoReg es ahora tAsignatura

#endif

// 2) Configuración de cubos (usa C de alumno.h o asignatura.h)
typedef struct {
    int nCubos;       // Número de cubos en el área prima (>8)
    int nCubosDes;    // Número de cubos área de desborde (>4)
    int nCuboDesAct;  // Primer cubo desborde con espacio
    float densidadMax;// Máxima densidad permitida
    float densidadMin;// Mínima densidad permitida
    int numReg;       // Total de registros en el archivo
    int numRegDes;    // Registros desbordados
} regConfig;

typedef struct {
    tipoReg reg[C];      // C viene de alumno.h o asignatura.h
    int numRegAsignados;
    int desbordado;      // 1 si se ha desbordado, 0 si no
} tipoCubo;

typedef struct {
    int cubo;     // Cubo asignado al registro
    int cuboDes;  // Cubo de desborde si lo hay, -1 si no
    int posReg;   // Posición dentro del cubo
} tPosicion;

// 3) Prototipos genéricos que usan tipoReg
int funcionHash(tipoReg *reg, int nCubos);
int cmpClave(tipoReg *reg1, tipoReg *reg2);


// 4) Operaciones de fichero hash
int busquedaHash(FILE *fHash, tipoReg *reg, tPosicion *posicion);
int modificarReg(FILE *fHash, tipoReg *reg, tPosicion *posicion);

// 5) Funciones ‘puente’ para los módulos de más alto nivel
int buscarReg(FILE *fichero, tipoReg *reg, void *clave);
int insertarReg(FILE *fichero, tipoReg *reg);
int creaHash( char *fichEntrada,  char *fichHash, regConfig *regC);
int leeHash( char *fichHash);
int insertar(FILE *f, tipoReg *reg, regConfig *regC);
int desborde(FILE *fHash, tipoReg *reg, regConfig *regC);


#endif // __DISPERSION_H
