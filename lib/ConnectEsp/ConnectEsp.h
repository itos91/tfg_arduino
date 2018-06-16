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
	    IPAddress _adress;
	    //Porto e ip do servidor ó que te conectas

	    int status = WL_IDLE_STATUS;

public:

	    ConnectEsp (char ssid[], char password[], int port, byte adress[]);
	    // Constructor ó que se lle pasa:
	    // - ssid = nome da rede do AP
	    // - password = contrasinal da rede do AP
	    // - port = porto do host http
	    // - address = direccion do host http

	    bool connectAp();
	    // Hay que llamar a este método en la función setup() para conectarse a la red
	    // Devuelve un String si se ha conectado a la WiFi

	    bool connectServer();
	    // Hay que llamar a este método en la función setup() para conectarse al servidor
	    // Devuelve un String si se ha conectado al servidor con éxito

			bool sendMessage(char message[]);
};


#endif
