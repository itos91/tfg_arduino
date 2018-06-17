#ifndef Teclado4x4_h
#define Teclado4x4_h

class Teclado4x4 {
  private:
    int _salidasFilas[4], * _entradasColumnas[4];
    char _caracteres[17];
    int _pulsado, _fila, _columna;
    unsigned long _t;
  public:
    Teclado4x4(int F1, int F2, int F3, int F4, int C1, int C2, int C3, int C4, char *caracteres);
    void configura();
    int comprueba();
};

#endif