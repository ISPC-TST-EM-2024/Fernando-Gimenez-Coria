#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Fibertel WiFi032 2.4GHz";
const char* password = "vuelalto67";

// Crear un servidor en el puerto 80
WebServer server(80);

const int ledPin = 2; // El LED integrado del ESP32 está en el pin 2

void handleRoot() {
  // Página web simple con dos botones para encender y apagar el LED
  server.send(200, "text/html", "<h1>Controla el LED</h1><p><a href=\"/on\"><button>Encender LED</button></a></p><p><a href=\"/off\"><button>Apagar LED</button></a></p>");
}

void handleLedOn() {
  digitalWrite(ledPin, HIGH); // Encender LED
  server.send(200, "text/html", "<p>LED encendido</p><p><a href=\"/\"><button>Volver</button></a></p>");
}

void handleLedOff() {
  digitalWrite(ledPin, LOW); // Apagar LED
  server.send(200, "text/html", "<p>LED apagado</p><p><a href=\"/\"><button>Volver</button></a></p>");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado al inicio

  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Configurar rutas del servidor web
  server.on("/", handleRoot);    // Página principal
  server.on("/on", handleLedOn); // Ruta para encender el LED
  server.on("/off", handleLedOff); // Ruta para apagar el LED

  server.begin(); // Iniciar el servidor
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient(); // Gestionar solicitudes HTTP
}
