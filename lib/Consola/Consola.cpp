#include "Consola.h"
#include <string.h>


Consola::Consola(int DB4, int DB5, int DB6, int DB7, int E1, int E2, int RS, int F1, int F2, int F3, int F4, int C1, int C2, int C3, int C4, char * caracteres):
    pantalla(DB4, DB5, DB6, DB7, E1, E2, RS),
    teclado(F1, F2, F3, F4, C1, C2, C3, C4, caracteres) {
}

void Consola::configura() {
  pantalla.configura();
  teclado.configura();
}

void Consola::visualizaEntero(int fila, int columna, int valor) {
  pantalla.posiciona(fila, columna);
  sprintf(_cadena,"%d",valor);
  pantalla.escribeCadena(_cadena);
}

void Consola::visualizaReal(int fila, int columna, float valor, int nCaracteres, int nDecimales) {
  pantalla.posiciona(fila, columna);
  dtostrf(valor, nCaracteres, nDecimales, _cadena);
  pantalla.escribeCadena(_cadena);
}

void Consola::visualizaCadena(int fila, int columna, char * cadena) {
  pantalla.posiciona(fila, columna);
  pantalla.escribeCadena(cadena);
}

void Consola::visualizaCadena(int fila, int columna, String cadena) {
  pantalla.posiciona(fila, columna);
  pantalla.escribeCadena(cadena);
}

char Consola::introduceCaracter() {
  char caracter;
  do {
    caracter = teclado.comprueba();
  } while (caracter == 0);
  return caracter;
}


void Consola::introduceCadena(int fila, int columna, char * validos, int nCaracteres, char * resultado) {
  int i;
  char caracter;
  pantalla.posiciona(fila, columna);
  for (i = 0; i < nCaracteres; i++)
      pantalla.escribeCaracter(' ');
  pantalla.posiciona(fila, columna);
  pantalla.muestraCursor(true);
  i = 0;
  do {
      caracter = introduceCaracter();
      if (strchr(validos, caracter) != NULL && i < nCaracteres) {
          resultado[i] = caracter;
          i++;
          pantalla.escribeCaracter(caracter);
      }
      if (caracter == 'i') {
          i--;
          pantalla.posiciona(fila, columna+i);
          pantalla.escribeCaracter(' ');
          pantalla.posiciona(fila, columna+i);
      }
  } while (caracter != 'e');
  pantalla.muestraCursor(false);
  resultado[i] = 0;
}

int Consola::introduceEntero(int fila, int columna, int nCaracteres) {
  introduceCadena(fila, columna, "0123456789", nCaracteres, _cadena);
  return atoi(_cadena);
}

float Consola::introduceReal(int fila, int columna, int nCaracteres) {
  introduceCadena(fila, columna, "0123456789.-", nCaracteres, _cadena);
  return atof(_cadena);
}


void Consola::borraPantalla() {
  pantalla.borra();
}
