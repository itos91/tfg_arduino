#ifndef PantallaMidas_h
#define PantallaMidas_h

#include <Arduino.h>

class PantallaMidas {
// Clase para el manejo de una pantalla LCD alfanumérica de 4 filas y 40 columnas modelo
// Midas MC44005A6W-FPTLW desde una placa Arduino. Se configura un bus de datos de 4 bits. 

  private:  // Recursos privados a esta clase
  
    int _DB4, _DB5, _DB6, _DB7, _E1, _E2, _RS;
    // Número de señales Arduino utilizadas para la conexión a la pantalla
    
    int _fila;  
    // Última fila posicionada 1...4
    
    void enviaOrden1(unsigned char orden);
    // Envía una orden al controlador 1 de la pantalla
    
    void enviaOrden2(unsigned char orden);
    // Envía una orden al controlador 2 de la pantalla
    
    void enviaOrden12(unsigned char orden);
    // Envía una orden a los controladores 1 y 2 de la pantalla
    
    void busDatos4Bits(unsigned char dato);
    // Establece un valor para el bus de datos, utilizando los 4 bits
    // menos significativos del parámetro
    
    void pulsoE1();
    // Pulso a nivel alto en señal E1 para transferencia con el controlador 1
    
    void pulsoE2();
    // Pulso a nivel alto en señal E1 para transferencia con el controlador 1

  public:  // Miembros públicos de esta clase
  
    PantallaMidas(int DB4, int DB5, int DB6, int DB7, int E1, int E2, int RS);
    // Constructor al que se le indica qué señales Arduino están conectadas a las 
    // señales de la pantalla
    
    void configura();
    // Método que hay que utilizar en setup() para configurar e inicializar los 
    // controladores de la pantalla
    
    void borra();
    // Borra toda la información mostrada en la pantalla
    
    void posiciona(int fila, int columna);
    // Posiciona el cursor en una fila (1...4) y columna (1...40)
    
    void escribeCadena(const char * cadena);
    // Escribe una cadena de caracteres en la posición actual del cursor

    void escribeCadena(const String cadena);
    
    void escribeCaracter(char caracter);
    // Escribe un carácter en la posición actual del cursor

    void muestraCursor(int muestralo);
    // Hace que el cursor sea visible en función del buleano que se pasa por parámetro

};

#endif