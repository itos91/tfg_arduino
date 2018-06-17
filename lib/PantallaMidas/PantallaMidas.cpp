#include <PantallaMidas.h>

PantallaMidas::PantallaMidas(int DB4, int DB5, int DB6, int DB7, int E1, int E2, int RS) {  
// Constructor al que se le indica qué señales Arduino están conectadas a las 
// señales de la pantalla

  _DB4 = DB4;
  _DB5 = DB5;
  _DB6 = DB6;
  _DB7 = DB7;
  _E1 = E1;
  _E2 = E2;
  _RS = RS;
  // Guarda los parámetros en datos privados
  
  _fila = 1;  // La fila inicial es la primera
}

void PantallaMidas::configura() {
// Método que hay que utilizar en setup() para configurar e inicializar los 
// controladores de la pantalla

  pinMode(_DB4, OUTPUT);
  pinMode(_DB5, OUTPUT);
  pinMode(_DB6, OUTPUT);
  pinMode(_DB7, OUTPUT);
  pinMode(_E1, OUTPUT);
  pinMode(_E2, OUTPUT);
  pinMode(_RS, OUTPUT);
  // Configura todas las señales como salidas digitales

  digitalWrite(_E1, LOW);
  digitalWrite(_E2, LOW);
  digitalWrite(_RS, LOW);
  // Pone a nivel bajo todas estas señales

  // A continuación se ejecuta la secuencia de inicialización de ambos controladores
  
  delay(20);  // Espera 20 ms

  busDatos4Bits(3);
  pulsoE1();
  pulsoE2();
  // Transfiere a ambos controladores el valor 3 

  delay(5);  // Espera 5 ms

  busDatos4Bits(3);
  pulsoE1();
  pulsoE2();
  // Transfiere a ambos controladores el valor 3 
  
  delay(1);  // Espera 1 ms

  busDatos4Bits(3);
  pulsoE1();
  pulsoE2();
  // Transfiere a ambos controladores el valor 3 
  
  delay(1);  // Espera 1 ms
  
  busDatos4Bits(2);
  pulsoE1();
  pulsoE2();
  // Transfiere a ambos controladores el valor 2 

  delay(1);  // Espera 1 ms

  enviaOrden12(0x2D);
  delay(1);
  //0000101101
  //0 0 0 0 1 DL N F - -
  // Function set: 
  // DL=0 establece bus de 4bits 
  // N=1 establece manejo de 2 filas
  // F=1 establece juego de caracteres de 5x11 puntos
  
  enviaOrden12(0x08);
  delay(1);
  // Display off

  borra();
  delay(2);
  // Clear display
  
  enviaOrden12(0x06);
  delay(1);
  // 0 0 0 0 0 0 0 0 0 1 ID SH
  // Entry mode set: 
  // ID=1 para que el cursor se mueva hacia derecha
  // SH=0 para que no haya desplazamiento de la pantalla
  
  enviaOrden12(0x0C);  // Display on
  delay(1);
}


void PantallaMidas::muestraCursor(int muestralo) {
// Hace que el cursor sea visible en función del buleano que se pasa por parámetro

  unsigned char orden1, orden2;
  
  if (muestralo) {  // Si hay que mostrarlo ...
    if (_fila < 3) {  // Si es para el controlador 1 ...
      orden1 = 0x0F;  // Muestra cursor en 1
      orden2 = 0x0C;  // Oculta cursor en 2
    } else {
      orden1 = 0x0C;  // Oculta cursor en 1
      orden2 = 0x0F;  // Muestra cursor en 2
    }
  } else {  // Si hay que ocultarlo ...
    orden1 = 0x0C;  // Oculta cursor en 1
    orden2 = 0x0C;  // Oculta cursor en 2
  }
  enviaOrden1(orden1);  // Envía la orden al controlador 1
  enviaOrden2(orden2);  // Envía la orden al controlador 2
}


void PantallaMidas::pulsoE1() {
// Pulso a nivel alto en señal E1 para transferencia con el controlador 1

  digitalWrite(_E1, HIGH);
  digitalWrite(_E1, LOW);
}

void PantallaMidas::pulsoE2() {
// Pulso a nivel alto en señal E2 para transferencia con el controlador 2

  digitalWrite(_E2, HIGH);
  digitalWrite(_E2, LOW);
}


void PantallaMidas::busDatos4Bits(unsigned char dato) {
// Establece un valor para el bus de datos, utilizando los 4 bits
// menos significativos del parámetro

  if (dato & 0x01)  // Si el bit 0 es un 1, entonces ...
      digitalWrite(_DB4, HIGH);  // pon la señal _DB4 a nivel alto
      else digitalWrite(_DB4, LOW);  // si no, pon la señal _DB4 a nivel bajo
      
  if (dato & 0x02)  // Si el bit 1 es un 1, entonces ...
      digitalWrite(_DB5, HIGH);  // pon la señal _DB5 a nivel alto
      else digitalWrite(_DB5, LOW);  // si no, pon la señal _DB5 a nivel bajo
      
  if (dato & 0x04)  // Si el bit 2 es un 1, entonces ...
      digitalWrite(_DB6, HIGH);  // pon la señal _DB6 a nivel alto
      else digitalWrite(_DB6, LOW);  // si no, pon la señal _DB6 a nivel bajo
      
  if (dato & 0x08)  // Si el bit 3 es un 1, entonces ...
      digitalWrite(_DB7, HIGH);  // pon la señal _DB7 a nivel alto
      else digitalWrite(_DB7, LOW);  // si no, pon la señal _DB7 a nivel bajo
}


void PantallaMidas::borra() {
// Borra toda la información mostrada en la pantalla

  enviaOrden12(0x01); 
  // Envía la orden de código 0x01 a los dos controladores
  
  delay(2);  // Espera 2 ms a que se termine de ejecutar
}


void PantallaMidas::escribeCadena(const char * cadena) {
// Escribe una cadena de caracteres en la posición actual del cursor

  int i;  // Contador para el bucle
  
  i = 0;  // Desde el comienzo de la cadena ...
  while(cadena[i])  // Mientras no se llegue a un byte con valor 0 ...
    escribeCaracter(cadena[i++]);  // Escribe el carácter y pasa al siguiente
}

void PantallaMidas::escribeCadena(const String cadena) {
  //Escribe una cadena de string en la poisicion actual del cursor

  int i;

  i = 0;
  while(cadena[i])
    escribeCaracter(cadena[i++]);
}


void PantallaMidas::posiciona(int fila, int columna) {
// Posiciona el cursor en una fila (1...4) y columna (1...40)

  int posicion;  // Posición en la memoria interna del controlador

  if (fila < 3) {   // Si es para el primer controlador ...
    
    posicion = (fila - 1) * 0x40 + columna - 1;
    // La primera posición comienza en 0 para la fila 1 y en 0x40 para la fila 2
    // Al avanzar en las columnas, se avanza en memoria a posiciones consecutivas
    
    enviaOrden1(0x80 | posicion);
    // Envía una orden al controlador 1 con la nueva posición del cursor
    
  } else {  // Lo mismo para el controlador 2
    posicion = (fila - 3) * 0x40 + columna - 1;
    enviaOrden2(0x80 | posicion);
  }
  
  delay(1);  // Espera 1 ms a que el cursor se posicione
  _fila = fila;  // Recuerda la fila donde está situado el cursor
}


void PantallaMidas::enviaOrden1(unsigned char orden) {
// Envía una orden al controlador 1 de la pantalla

  digitalWrite(_RS, LOW);  // Pone la señal RS a nivel bajo
  
  busDatos4Bits(orden >> 4);  // Pone los 4 bits más significativos en el bus de datos
  pulsoE1();  // Pulso en E1 para transferir esos bits
  busDatos4Bits(orden & 0x0F);  // Pone los 4 bits menos significativos en el bus de datos
  pulsoE1();  // Pulso en E1 para transferir esos bits
}


void PantallaMidas::enviaOrden2(unsigned char orden) {
// Envía una orden al controlador 2 de la pantalla

  digitalWrite(_RS, LOW);  // Pone la señal RS a nivel bajo
  
  busDatos4Bits(orden >> 4);  // Pone los 4 bits más significativos en el bus de datos
  pulsoE2();  // Pulso en E2 para transferir esos bits
  busDatos4Bits(orden & 0x0F);  // Pone los 4 bits menos significativos en el bus de datos
  pulsoE2();  // Pulso en E2 para transferir esos bits
}


void PantallaMidas::enviaOrden12(unsigned char orden) {
// Envía una orden a ambos controladores

  enviaOrden1(orden);   // Envía la orden al controlador 1
  enviaOrden2(orden);   // Envía la orden al controlador 2
}


void PantallaMidas::escribeCaracter(char caracter) {
// Envía un carácter a la pantalla, que se mostrará en la posición actual del cursor. 
// La posición del cursor se incrementa

  digitalWrite(_RS, HIGH);   // Pone la señal RS a nivel alto
  
  busDatos4Bits(caracter >> 4);  // Pone los 4 bits más significativos en el bus de datos
  if (_fila < 3)  // Si es para el controlador 1 ...
    pulsoE1();   // pulso en E1 para transferir esos bits al controlador 1
    else pulsoE2();  // si no, pulso en E2 para transferir esos bits al controlador 2
    
  busDatos4Bits(caracter & 0x0F);    // Pone los 4 bits menos significativos en el bus de datos
  if (_fila < 3)  // Si es para el controlador 1 ...
    pulsoE1();   // pulso en E1 para transferir esos bits al controlador 1
    else pulsoE2();  // si no, pulso en E2 para transferir esos bits al controlador 2
    
  delay(1);  // Retardo de 1 ms para esperar a que se escriba el carácter
}