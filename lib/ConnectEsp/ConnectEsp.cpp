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
  _client.flush();

  // if there's a successful connection
  if (_client.connect(_host, _port)) {
    Serial.println("Conectando co host...");

    // send the HTTP PUT request
    _client.println(message);
    _client.print("Host: ");
    _client.println(_host);
    _client.println("Connection: close");
    _client.println();
  }
  else
  {
    // if you couldn't make a connection
    Serial.println("Connection failed");
  }
}


bool ConnectEsp::get_Encargo_Completado_django()
{

  while(!_client.available());
  String jsonString;
  while (_client.available())
  {
    jsonString = _client.readStringUntil('\r');
  }
  Serial.println(jsonString);
  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(jsonString);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    //return;
  }
  int count = root["count"];
  JsonArray& results = root["results"];

  for (int i = 0; i < count; i++)
  {
    JsonObject& results_aux = results[i];
    bool completado = results_aux["completado"];
    if(!completado)
    {
      pk_encargo = results_aux["pk"];
      return true;
    }
    return false;
  }
}

int ConnectEsp::get_producto_Encargo_django()
{

  while(!_client.available());
  String jsonString;
  while (_client.available())
  {
    jsonString = _client.readStringUntil('\r');
  }
  Serial.println(jsonString);
  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(jsonString);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    //return;
  }
  int count = root["count"];

  JsonArray& results = root["results"];

  int count_productos_encargo = 0;

  for (int i = 0; i < count; i++)
  {
    JsonObject& results_aux = results[i];
    int pk_encargo_aux = results_aux["encargo"];

    if(pk_encargo_aux = pk_encargo)
    {
      pk_producto[count_productos_encargo] = results_aux["producto"];
      cantidade_producto[count_productos_encargo] = results_aux["cantidade"];
      count_productos_encargo++;
    }
  }
  return count_productos_encargo;
}

void ConnectEsp::get_Localizacion_django(int num_producto)
{

  while(!_client.available());
  String jsonString;
  while (_client.available())
  {
    jsonString = _client.readStringUntil('\r');
  }
  Serial.println(jsonString);
  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(jsonString);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    //return;
  }
  char * aux;
  aux = root["localizacion"];
  localizacion_producto[num_producto]= aux;
  aux = root["name"];
  name_producto[num_producto] = aux;
}
