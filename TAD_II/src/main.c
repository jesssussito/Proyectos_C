#include <stdio.h>
#include <stdlib.h>
#include "dispersion.h"    // regConfig, creaHash, leeHash, buscarReg, insertarReg
#ifdef ALUM
  #include "alumno.h"      // tAlumno, buscar, modificar (alt. de buscarReg/modificarReg)
#endif
#ifdef ASIG
  #include "asignatura.h"  // tAsignatura, buscar, modificar
#endif
int main(int argc,char *argv[]){
    regConfig regC;
    char ficheroEnt[64], ficheroHash[64];
    int error, desbordados;

    /* 1) Parámetros y configuración */
    #ifdef ALUM
      strcpy(ficheroEnt,  "../datos/alumnos.dat");
      strcpy(ficheroHash, "../datos/alumnosC.hash");
      regC.nCubos = 15;
    #endif
    #ifdef ASIG
      strcpy(ficheroEnt,  "../datos/asignaturas.dat");
      strcpy(ficheroHash, "../datos/asignaturasC.hash");
      regC.nCubos = 10;
    #endif
    regC.nCubosDes   = 4;    // cubos de desborde :contentReference[oaicite:0]{index=0}:contentReference[oaicite:1]{index=1}
    regC.densidadMax = 80.0;
    regC.densidadMin = 40.0;

    /* 2) Crear el hash desde el fichero de entrada */
    desbordados = creaHash(ficheroEnt, ficheroHash, &regC);
    if (desbordados < 0) {
        fprintf(stderr, "Error %d en creaHash\n", desbordados);
        return 1;
    }
    printf("Hash creado. Registros desbordados: %d\n\n", desbordados);

    /* 3) Mostrar la organización actual */
    leeHash(ficheroHash);  // lee todos los cubos y muestra su contenido :contentReference[oaicite:2]{index=2}:contentReference[oaicite:3]{index=3}

    /* 4) Búsqueda y modificación de un registro de ejemplo */
    #ifdef ALUM
      printf("\n--- BÚSQUEDA/MODIFICACIÓN ALUMNO ---\n");
      error = buscar(ficheroHash, "8663873");              // función en alumnos.c :contentReference[oaicite:4]{index=4}:contentReference[oaicite:5]{index=5}
      if (error < 0) printf("Error %d en buscar alumno\n", error);
      error = modificar(ficheroHash, "8663873", "Sevilla");
      if (error < 0) printf("Error %d en modificar alumno\n", error);
      buscar(ficheroHash, "8663873");
    #endif

    #ifdef ASIG
      printf("\n--- BÚSQUEDA/MODIFICACIÓN ASIGNATURA ---\n");
      error = buscar(ficheroHash, 101116);                 // función en asignatura.c :contentReference[oaicite:6]{index=6}:contentReference[oaicite:7]{index=7}
      if (error < 0) printf("Error %d en buscar asignatura\n", error);
      error = modificar(ficheroHash, 101116, 4.5f, 1.5f);
      if (error < 0) printf("Error %d en modificar asignatura\n", error);
      buscar(ficheroHash, 101116);
    #endif

    /* 5) Inserción de un nuevo registro */
    {
      FILE *f = fopen(ficheroHash, "r+b");
      if (!f) {
        perror("fopen");
        return 1;
      }
      tipoReg nuevo;
      #ifdef ALUM
        // rellenar nuevo alumno
        strcpy(nuevo.dni,       "12345678");
        strcpy(nuevo.nombre,    "Juan");
        strcpy(nuevo.ape1,      "Pérez");
        strcpy(nuevo.ape2,      "García");
        strcpy(nuevo.provincia, "Madrid");
      #endif
      #ifdef ASIG
        // rellenar nueva asignatura
        nuevo.codigo       = 202025;
        strcpy(nuevo.nombre,      "Nueva Asignatura");
        nuevo.curso         = '3';
        nuevo.creditosT    = 3.0f;
        nuevo.creditosP    = 1.0f;
        nuevo.tipo         = 'O';
        nuevo.cuatrimestre = '1';
        nuevo.numGrT       = 2;
        nuevo.numGrP       = 1;
      #endif

      int cuboIns = insertarReg(f, &nuevo);
      if (cuboIns < 0)
        printf("No se pudo insertar el registro (área de desborde llena)\n");
      else
        printf("Registro insertado en el cubo %d\n", cuboIns);

      fclose(f);
    }

    /* 6) Mostrar de nuevo para ver la inserción */
    printf("\n--- ORGANIZACIÓN TRAS INSERCIÓN ---\n");
    leeHash(ficheroHash);

    return 0;
}