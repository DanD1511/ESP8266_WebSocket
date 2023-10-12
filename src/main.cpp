#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const char *ssid = "HUAWEI nova 5T";
const char *password = "Eyleen0129";

const int webSocketPort = 81;
WebSocketsServer webSocket = WebSocketsServer(webSocketPort);
const int ledPin = 2; // Pin para el LED.

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Conectado desde %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
    }
    break;
    case WStype_TEXT:
      Serial.printf("[%u] Recibido: %s\n", num, payload);
      int valorRecibido = atoi((char *)payload); // Convertir el payload a un entero.
      int pwmValue = map(valorRecibido, 0, 180, 0, 255); // Mapear el valor entre 0 y 180 a un valor PWM entre 0 y 255.
      analogWrite(ledPin, pwmValue); // Establecer el valor de PWM para controlar la intensidad del LED.
      break;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }

  // Muestra la dirección IP de la ESP8266 en el monitor serie
  Serial.print("Dirección IP de la ESP8266: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  pinMode(ledPin, OUTPUT); // Configurar el pin del LED como salida.

  Serial.println("Servidor WebSocket iniciado");
}

void loop() {
  webSocket.loop();
  // Puedes agregar tu lógica adicional en el bucle si es necesario
}


// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <WebSocketsServer.h>

// const char *ssid = "HomeRD";
// const char *password = "F10773929";

// const int webSocketPort = 81;
// WebSocketsServer webSocket = WebSocketsServer(webSocketPort);

// void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
//   switch (type) {
//     case WStype_DISCONNECTED:
//       Serial.printf("[%u] Desconectado!\n", num);
//       break;
//     case WStype_CONNECTED:
//       {
//         IPAddress ip = webSocket.remoteIP(num);
//         Serial.printf("[%u] Conectado desde %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
//       }
//       break;
//     case WStype_TEXT:
//       Serial.printf("[%u] Recibido: %s\n", num, payload);
//       // Puedes agregar tu lógica aquí para procesar el mensaje recibido
//       break;
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Conectando a la red WiFi...");
//   }
  
//   // Muestra la dirección IP de la ESP8266 en el monitor serie
//   Serial.print("Dirección IP de la ESP8266: ");
//   Serial.println(WiFi.localIP());

//   webSocket.begin();
//   webSocket.onEvent(webSocketEvent);

//   Serial.println("Servidor WebSocket iniciado");
// }

// void loop() {
//   webSocket.loop();
//   // Puedes agregar tu lógica adicional en el bucle si es necesario
// }
