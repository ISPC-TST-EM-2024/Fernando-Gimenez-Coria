#include <WiFi.h>
#include <Arduino.h>

const char* ssid = "tu_SSID";  // Reemplaza por el nombre de tu red
const char* password = "tu_password";  // Reemplaza por la contraseña de tu red

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Intentar conectarse al Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // No se necesita nada en el loop para esta parte
}
