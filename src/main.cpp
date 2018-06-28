#include <Arduino.h>
#include "Consola.h"
#include <ConnectEsp.h>
#include <string.h>
#include <stdio.h>

#define SALCEDA

//variables estáticas tipo String para a conexión AP
#if defined(CARBA)
  static char ssid[] = "Quesada";
  static char pass[] = "987ingenieros";
#endif

#if defined(CARBA2)
  static char ssid[] = "MiFibra-48A3";
  static char pass[] = "s5HTY5J7";
#endif

#if defined(SALCEDA)
  static char ssid[] = "HUAWEI-Cw4a";
  static char pass[] = "9RR3VAxS";
#endif

//variable estática tipo String do host do servidor
static char host[]= "192.168.100.4";
static int port = 8000;

//declaramos constructor da clase ConnectEsp
ConnectEsp ap (ssid, pass, port, host);

//declaramos constructor da clase Consola
Consola consola(32, 33, 34, 35, 36, 37, 38, 22, 23, 24, 25, 26, 27, 28, 29, "789s456-123d.0ei");

void setup()
{
  // put your setup code here, to run once:
  consola.configura();
  // Configura as señaies Arduino e envía a secuencia de órdenes de inicialización
  // á pantalla e teclado

  ap.connectAP();
  consola.visualizaCadena(-1, 0, "Conectouse a rede: ");
  consola.visualizaCadena(-1, 20, ssid);
  consola.visualizaCadena(4,1,"Pulsa ENT para continuar");

  while(consola.introduceCaracter() != 'e');
  consola.borraPantalla();
}

void loop()
{
    // put your main code here, to run repeatedly:
    ap.httpRequest("GET /encargos/ HTTP/1.0");

    if (ap.get_Encargo_Completado_django())
    {
      consola.visualizaCadena(-1, 0, "Encargo con id: ");
      consola.visualizaEntero(-1, 18, ap.get_pk_encargo());
      consola.visualizaCadena(4,1,"Pulsa ENT para continuar");

      while(consola.introduceCaracter() != 'e');
      consola.borraPantalla();

      ap.httpRequest("GET /detalle_encargo/ HTTP/1.0");
      int n_p = 0;

      n_p = ap.get_producto_Encargo_django();
      Serial.print("n_p: ");
      Serial.println(n_p);

      if (n_p > 0)
      {
        for (int i = 0; i < n_p; i++)
        {
          Serial.print("Producto numero: ");
          Serial.println(ap.get_pk_producto(i));
          char to_send[30];
          sprintf(to_send,"GET /productos/%d/ HTTP/1.0",ap.get_pk_producto(i));
          ap.httpRequest(to_send);
          ap.get_Localizacion_django(i);

          char* nome_terminal = ap.get_name_producto(i);
          Serial.println(nome_terminal);
          char* localizacion_terminal = ap.get_localizacion_producto(i);

          consola.visualizaCadena(1, 0, "Producto: ");
          consola.visualizaCadena(1, 15, nome_terminal);
          consola.visualizaCadena(2, 0, "Cantidade: ");
          consola.visualizaEntero(2, 15, ap.get_cantidade_producto(i));
          consola.visualizaCadena(3, 0, "Localizacion: ");
          consola.visualizaCadena(3, 15, localizacion_terminal);
          consola.visualizaCadena(4,0,"Pulsa ENT cando acabes");

          while(consola.introduceCaracter() != 'e');
          consola.borraPantalla();
        }
        ap.post_encargo_completado();

        consola.visualizaCadena(-1, 0, "Encargo completado");
        consola.visualizaCadena(4,0,"Pulsa ENT para ver o seguinte");

        while(consola.introduceCaracter() != 'e');
        consola.borraPantalla();
      }
      else
      {
        ap.post_encargo_completado();
        consola.visualizaCadena(-1, 0, "Non hai productos para este encargo");
        consola.visualizaCadena(4,1,"Pulsa ENT para ver o seguinte");

        while(consola.introduceCaracter() != 'e');
        consola.borraPantalla();
      }
    }
    else {
      consola.visualizaCadena(-1, 0, "Non hai encargos");
      consola.visualizaCadena(4,1,"Pulsa ENT para actualizar");

      while(consola.introduceCaracter() != 'e');
      consola.borraPantalla();
    }
}
