#ifndef ConnectEsp_h
#define ConnectEsp_h

#include <Arduino.h>
#include <Ethernet.h>
#include <WiFiEsp.h>
#include <ArduinoJson.h>
// Para utilizar clases de comunicación serie


class ConnectEsp
{

private:
	    WiFiEspClient _client;
      //constructor da clase WifiEspClient

	    char *_ssid;
	    char *_pass;
	    //Nome e contraseñas do AP ó que te conectas
	    int _port;
	    char *_host;
	    //Porto e ip do servidor ó que te conectas

	    int status = WL_IDLE_STATUS;
			int pk_encargo;
			int * pk_producto;
			int * cantidade_producto;
			String * name_producto;
			String *localizacion_producto;

public:

	    ConnectEsp (char ssid[], char password[], int port, char host[]);
	    // Constructor ó que se lle pasa:
	    // - ssid = nome da rede do AP
	    // - password = contrasinal da rede do AP
	    // - port = porto do host http
	    // - host = direccion do host http

	    void connectAP();
	    // Hay que llamar a este método en la función setup() para conectarse a la red
	    // Devolve True si se conectou co AP con éxito

	    void httpRequest(char message[]);
	    // Hay que llamar a este método en la función setup() para conectarse al servidor
	    // Devolve True si se conectou servidor con éxito
			bool get_Encargo_Completado_django();
			// Función que fai un GET a tabla Encargo e devolve se hai encargos

			int get_producto_Encargo_django();
			//funcion que fai un GET a tabla Detalle_Encargo e devolve o numero de productos para o encargo

			void get_Localizacion_django(int num_producto);

			//getters de variables privadas
			inline int get_pk_Producto(int index){return pk_producto[index];}
			inline String get_localizacion_producto(int index){return localizacion_producto[index];}
			inline String get_name_Producto(int index){return name_producto[index];}
			inline int get_cantidade_Producto(int index){return cantidade_producto[index];}
			inline int get_pk_Encargo(){return pk_encargo;}
};


#endif
