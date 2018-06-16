#include "ConnectEsp.h"


ConnectEsp::ConnectEsp(char ssid[], char password[], int port, byte adress[]) {
  // Constructor ó que se lle pasa:
  // - ssid = nome da rede do AP
  // - password = contrasinal da rede do AP
  // - port = porto do host http
  // - address = direccion do host http (array de bytes)

  _ssid = ssid;
  _pass = password;
  _port = port;
  _adress = IPAddress(adress);
  // Garda no obxecto estos parametros
}


bool ConnectEsp::connectAP() {
  // En el setup() del sketch hay que llamar a este método para conectarse a la red
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(115200);
  // initialize ESP module

    WiFi.init(&Serial1);

    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      // don't continue
      while (true);
    }

    while (status != WL_CONNECTED){
      Serial.print("Conectandose a rede: ");
      Serial.println(_ssid);
      status = WiFi.begin(_ssid,_pass);
    }

    Serial.println("Estás conectado á rede");

    return true;
}

bool ConnectEsp::connectServer() {
    //En el setup() del sketch hay que llamar a este método para conectarse al servidor
    while (!_client.connect(_adress, 80)) {
      Serial.println("Non se pode conectar o servidor http");
    }
    Serial.println("Conectado o servidor");

    return true;

}

bool ConnectEsp::sendMessage(char message[]) {
  return true;
}
