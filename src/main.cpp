#include <Arduino.h>
#include "Consola.h"
#include <ConnectEsp.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SALCEDA

//variables estáticas tipo String para a conexión AP
#if CARBA
  static char ssid[] = "Quesada";
  static char pass[] = "987ingenieros";
#endif

#if defined(SALCEDA)
  static char ssid[] = "HUAWEI-Cw4a";
  static char pass[] = "9RR3VAxS";
#endif

//variable estática tipo String do host do servidor
static char host[]= "192.168.100.3";
static int port = 8000;

//variable tipo boolean que indica se o operario está facendo un encargo
bool encargoCompletado = false;

unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10000L; // delay between updates, in milliseconds

//declaramos constructor da clase ConnectEsp
ConnectEsp ap (ssid, pass, port, host);

//declaramos constructor da clase Consola
Consola consola(32, 33, 34, 35, 36, 37, 38, 22, 23, 24, 25, 26, 27, 28, 29, "789s456-123d.0ei");

void setup() {
    // put your setup code here, to run once:
    consola.configura();
    // Configura as señaies Arduino e envía a secuencia de órdenes de inicialización
    // á pantalla e teclado

    ap.connectAP();
    consola.visualizaCadena(0, 0, "Conectouse o AP");
    consola.visualizaCadena(4,1,"Pulsa ENT para continuar");

    while(consola.introduceCaracter() != 'e');
}

void loop() {
    // put your main code here, to run repeatedly:
    while(!encargoCompletado)
    {
      ap.readServer();
      // if 10 seconds have passed since your last connection,
      // then connect again and send data
      if (millis() - lastConnectionTime > postingInterval) {
        ap.httpRequest("GET /encargos/1 HTTP/1.1");
        // note the time that the connection was made
        lastConnectionTime = millis();
      }
    }
}
