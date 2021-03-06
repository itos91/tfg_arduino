#ifndef ConnectEsp_h
#define ConnectEsp_h

#include <Arduino.h>
#include <Ethernet.h>
#include <WiFiEsp.h>
#include <ArduinoJson.h>
#include <stdio.h>


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
			int pk_producto[6];
			int cantidade_producto[6];
			char* name_producto[6];
			char* localizacion_producto[6];
			//variables para almacenar request de Json

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
			//función que fai un GET a tabla Producto e lle pasa por parametro o pk do producto

			void post_encargo_completado();
			//función que fai un PUT e modifica o rexitro "Completado" a True

			//getters de variables privadas
			inline int get_pk_producto(int index){return pk_producto[index];}
			inline char * get_localizacion_producto(int index){return localizacion_producto[index];}
			inline char * get_name_producto(int index){return name_producto[index];}
			inline int get_cantidade_producto(int index){return cantidade_producto[index];}
			inline int get_pk_encargo(){return pk_encargo;}
			//setters de variables privadas
			inline void set_pk_producto(int index, int producto){pk_producto[index] = producto;}
			inline void set_localizacion_producto(int index, char * localizacion){localizacion_producto[index] = localizacion;}
			inline void set_name_producto(int index, char * name){name_producto[index] = name;}
			inline int set_cantidade_producto(int index, int cantidade){cantidade_producto[index] = cantidade;}
			inline int set_pk_encargo(int encargo){pk_encargo = encargo;}
};


#endif
