#ifndef ConnectEsp_h
#define ConnectEsp_h

#include <Arduino.h>
#include <Ethernet.h>
#include <WiFiEsp.h>
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
			void readServer();
};


#endif
