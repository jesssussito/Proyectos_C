#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "dispersion.h"
#ifdef ALUM
  #include "alumno.h"       /* aquí está buscar(...) y modificar(...) para tAlumno */
#elif defined(ASIG)
  #include "asignatura.h"   /* buscar(...) y modificar(...) para tAsignatura */
#endif
int main(void){
    int error;

    #ifdef ALUM
      printf("\n--- BÚSQUEDA/MODIFICACIÓN ALUMNO ---\n");

      // 1) Buscar antes de modificar
      error = buscar("../datos/alumnosC.hash", "8663873");
      if (error < 0) {
          printf("Error %d en la función buscar alumno\n", error);
      } else {
          printf("Alumno encontrado en el cubo %d\n", error);
      }

      // 2) Modificar provincia
      error = modificar("../datos/alumnosC.hash", "8663873", "Sevilla");
      if (error < 0) {
          printf("Error %d en la función modificar alumno\n", error);
      } else {
          printf("Alumno modificado correctamente en el cubo %d\n", error);
      }

      // 3) Volver a buscar para comprobar
      error = buscar("../datos/alumnosC.hash", "8663873");
      if (error < 0) {
          printf("Error %d en la función buscar alumno\n", error);
      } else {
          printf("Después de modificar, alumno en cubo %d\n", error);
      }
    #endif

    #ifdef ASIG
      printf("\n--- BÚSQUEDA/MODIFICACIÓN ASIGNATURA ---\n");

      // 1) Buscar antes de modificar
      error = buscar("../datos/asignaturasC.hash", 101116);
      if (error < 0) {
          printf("Error %d en la función buscar asignatura\n", error);
      } else {
          printf("Asignatura encontrada en el cubo %d\n", error);
      }

      // 2) Modificar créditos
      error = modificar("../datos/asignaturasC.hash", 101116, 4.5f, 1.5f);
      if (error < 0) {
          printf("Error %d en la función modificar asignatura\n", error);
      } else {
          printf("Asignatura modificada correctamente en el cubo %d\n", error);
      }

      // 3) Volver a buscar para comprobar
      error = buscar("../datos/asignaturasC.hash", 101116);
      if (error < 0) {
          printf("Error %d en la función buscar asignatura\n", error);
      } else {
          printf("Después de modificar, asignatura en cubo %d\n", error);
      }
    #endif

    return 0;
}


