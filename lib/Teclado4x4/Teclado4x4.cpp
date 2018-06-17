#include <Teclado4x4.h>
#include <Arduino.h>

Teclado4x4::Teclado4x4(int F1, int F2, int F3, int F4, int C1, int C2, int C3, int C4, char *caracteres) {
  _salidasFilas[0] = F1;
  _salidasFilas[1] = F2;
  _salidasFilas[2] = F3;
  _salidasFilas[3] = F4;
  _entradasColumnas[0] = C1;
  _entradasColumnas[1] = C2;
  _entradasColumnas[2] = C3;
  _entradasColumnas[3] = C4;
  strcpy(_caracteres,caracteres);
  // Guarda los parámetros en datos privados
}


void Teclado4x4::configura() {
  int i;
  //memcpy (_salidasFilas, salidasFilas, 4 * sizeof(int));
  //memcpy (_entradasColumnas, entradasColumnas, 4 * sizeof(int));
  //strcpy (_caracteres, caracteres);
  for (i = 0; i < 4; i++)
    pinMode(_entradasColumnas[i], INPUT_PULLUP);
  _pulsado = 0;
  _t = millis();
}


int Teclado4x4::comprueba () {
  int iSalida, iEntrada;

  if (millis() - _t < 10) 
    return 0;
    else _t = millis();

  if (_pulsado) {
    pinMode(_salidasFilas[_fila], OUTPUT);
    digitalWrite(_salidasFilas[_fila], LOW);
    _pulsado = digitalRead(_entradasColumnas[_columna]) == LOW;
    pinMode(_salidasFilas[_fila], INPUT);    
    if (_pulsado)
      return 0;
  }
  
  if (! _pulsado) {
    for (iSalida = 0; iSalida < 4 && ! _pulsado; iSalida ++) {
      pinMode(_salidasFilas[iSalida], OUTPUT);
      digitalWrite(_salidasFilas[iSalida], LOW);
      for (iEntrada = 0; iEntrada < 4 && ! _pulsado; iEntrada ++) {
        if (digitalRead(_entradasColumnas[iEntrada]) == LOW) {
          _pulsado = 1;
          _fila = iSalida;
          _columna = iEntrada;
        }
      }
      pinMode(_salidasFilas[iSalida], INPUT);
    }
  }
  
  if (_pulsado)
    return _caracteres[_fila * 4 + _columna];
  else return 0;
}