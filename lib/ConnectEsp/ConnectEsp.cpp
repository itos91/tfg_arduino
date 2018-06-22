#include "ConnectEsp.h"


ConnectEsp::ConnectEsp(char ssid[], char password[], int port, char host[])
{
  // Constructor ó que se lle pasa:
  // - ssid = nome da rede do AP
  // - password = contrasinal da rede do AP
  // - port = porto do host http
  // - address = direccion do host http (array de bytes)

  _ssid = ssid;
  _pass = password;
  _port = port;
  _host = host;
  // Garda no obxecto estos parametros
}


void ConnectEsp::connectAP()
{
  // En el setup() del sketch hay que llamar a este método para conectarse a la red
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(115200);
  // initialize ESP module

    WiFi.init(&Serial1);

    if (WiFi.status() == WL_NO_SHIELD)
    {
      Serial.println("WiFi shield not present");
      // don't continue
      while (true);
    }

    while (status != WL_CONNECTED)
    {
      Serial.print("Conectandose a rede: ");
      Serial.println(_ssid);
      status = WiFi.begin(_ssid,_pass);
    }

    Serial.println("Estás conectado á rede");
}

void ConnectEsp::httpRequest(char message[])
{
  // close any connection before send a new request
  // this will free the socket on the WiFi shield
  _client.stop();

  // if there's a successful connection
  if (_client.connect(_host, _port)) {
    Serial.println("Conectando co host...");

    // send the HTTP PUT request
    _client.println(message);
    _client.println(F("Host: 192.168.100.3"));
    _client.println("Connection: close");
    _client.println();
  }
  else
  {
    // if you couldn't make a connection
    Serial.println("Connection failed");
  }
}

void ConnectEsp::readServer()
{
  while (_client.available()) {
    char c = _client.read();
    Serial.write(c);
  }
}
