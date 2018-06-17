#ifndef CONSOLA_H_
#define CONSOLA_H_

#include "PantallaMidas.h"
#include "Teclado4x4.h"

class Consola {
  // Un objeto de esta clase representa a una consola compuesta por un teclado y una pantalla
  
  private:
      PantallaMidas pantalla;
      Teclado4x4 teclado;
      // Cada objeto Consola contiene objetos para manejar el teclado y la pantalla
      
      char _cadena[41];
      
  public: 
  
      Consola(int DB4, int DB5, int DB6, int DB7, int E1, int E2, int RS, int F1, int F2, int F3, int F4, int C1, int C2, int C3, int C4, char * caracteres);
      // Constructor al que le proporcionamos los datos necesarios para inicializar la pantalla y el teclado
      
      void configura();  // Utilizado en el setup() para configurar estos dispositivos
      
      void visualizaEntero(int fila, int columna, unsigned int valor);
      void visualizaReal(int fila, int columna, float valor, int nCaracteres, int nDecimales);
      void visualizaCadena(int fila, int columna, char * cadena);  
      void visualizaCadena(int fila, int columna, String cadena);
      // Para visualizar información en pantalla
      
      char introduceCaracter();
      int introduceEntero(int fila, int columna, int nCaracteres);
      float introduceReal(int fila, int columna, int nCaracteres);
      void introduceCadena(int fila, int columna, char * validos, int nCaracteres, char * resultado);
      // Para introducir información por teclado
      
      void borraPantalla();
      // Para borrar la pantalla
};

#endif
