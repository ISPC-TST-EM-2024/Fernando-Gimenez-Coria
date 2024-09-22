![logo](../../rsc/visuales/LOGO.png)  
  
# - Práctica 3: Servidor Web Simple con Wi-Fi  

## Objetivo:   
- Crear un servidor web en el ESP32 para controlar el LED integrado desde un navegador web.
## Librerias necesarias:
- WiFi.h: para la conexión Wi-Fi.
- WebServer.h: para implementar el servidor web.
## Pasos a seguir:
### 1- Configurar conexion wifi:
- Conectar el ESP32 a una red Wi-Fi.   

```cpp  
#include <WiFi.h>

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
```

### 2- Implementar el servidor web y controlar el LED:
- Configurar un servidor web que escuche el puerto 80.
- Crear una página web simple con dos botones para encender y apagar el LED.
- Definir rutas para encender y apagar el LED
- Implementar la lógica para cambiar el estado del LED según las peticiones recibidas.   

```cpp  
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "tu_SSID";
const char* password = "tu_password";

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

```     
## Explicación del código  
### 1. Incluir Librerías
```cpp

#include <WiFi.h>
#include <WebServer.h>  
```
**WiFi.h:** Esta librería maneja la conexión del ESP32 a la red Wi-Fi.  

**WebServer.h:** Esta librería es esencial para crear un servidor HTTP en el ESP32. Permite definir rutas que responden a solicitudes del navegador.  

### 2. Definir las Credenciales Wi-Fi
```cpp

const char* ssid = "tu_SSID";
const char* password = "tu_password";
```  
Aquí se define el nombre de la red Wi-Fi (ssid) y la contraseña. El ESP32 necesita esta información para conectarse a la red inalámbrica.

### 3. Crear el Servidor Web
```cpp

WebServer server(80);  
```
Aquí se instancia un servidor web en el puerto 80, que es el puerto por defecto para HTTP. El servidor esperará solicitudes en este puerto.

### 4. Pin del LED
```cpp

const int ledPin = 2;  
```
El LED integrado en el ESP32 está en el pin 2. Este será el pin que se controlará con el servidor web.

### 5. Manejo de la Página Principal ("/")
```cpp

void handleRoot() {
  server.send(200, "text/html", "<h1>Controla el LED</h1><p><a href=\"/on\"><button>Encender LED</button></a></p><p><a href=\"/off\"><button>Apagar LED</button></a></p>");
} 
```
**handleRoot():** Esta función responde a la solicitud de la ruta principal ("/"). Cuando un usuario accede a la página principal del servidor, esta función envía un código HTML simple que contiene dos botones: uno para encender y otro para apagar el LED.  
**server.send(200, "text/html", ...):** Envía una respuesta HTTP al navegador. El código 200 indica que la solicitud fue exitosa y el contenido es de tipo text/html.  

### 6. Manejo para Encender el LED ("/on")
```cpp

void handleLedOn() {
  digitalWrite(ledPin, HIGH); // Encender LED
  server.send(200, "text/html", "<p>LED encendido</p><p><a href=\"/\"><button>Volver</button></a></p>");
}  
```
**digitalWrite(ledPin, HIGH):** Enciende el LED al poner el pin 2 en ALTO (5V).
Esta ruta ("/on") responde al clic en el botón Encender LED. Muestra un mensaje en la página confirmando que el LED está encendido, y ofrece un botón para volver a la página principal.  

### 7. Manejo para Apagar el LED ("/off")
```cpp

void handleLedOff() {
  digitalWrite(ledPin, LOW); // Apagar LED
  server.send(200, "text/html", "<p>LED apagado</p><p><a href=\"/\"><button>Volver</button></a></p>");
}   
```
**digitalWrite(ledPin, LOW):** Apaga el LED al poner el pin 2 en BAJO (0V).
Esta ruta ("/off") responde al clic en el botón Apagar LED. Muestra un mensaje confirmando que el LED está apagado, y ofrece un botón para volver a la página principal.  

### 8. Inicialización en setup()
```cpp

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Apagar el LED al inicio

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);   // Definir la ruta para la página principal
  server.on("/on", handleLedOn); // Ruta para encender el LED
  server.on("/off", handleLedOff); // Ruta para apagar el LED

  server.begin(); // Iniciar el servidor web
  Serial.println("Servidor HTTP iniciado");
}  
```
`Serial.begin(115200):` Inicia la comunicación serie para poder monitorear el proceso de conexión a la red y la operación del servidor desde el monitor serie.
`pinMode(ledPin, OUTPUT):` Configura el pin 2 como salida para poder controlar el LED.
`digitalWrite(ledPin, LOW):` Asegura que el LED esté apagado cuando el sistema arranca.
`WiFi.begin(ssid, password):` Inicia el proceso de conexión a la red Wi-Fi con las credenciales proporcionadas.
`while (WiFi.status() != WL_CONNECTED):` Espera hasta que el ESP32 se conecte a la red Wi-Fi, mostrando un mensaje cada segundo.
`server.on("/", handleRoot):` Asocia la ruta / (página principal) con la función handleRoot, que genera la página web con los botones.
`server.on("/on", handleLedOn):` Asocia la ruta /on para encender el LED.
`server.on("/off", handleLedOff):` Asocia la ruta /off para apagar el LED.
`server.begin():` Inicia el servidor web.  

### 9. Gestión de Solicitudes en loop()
```cpp
 
void loop() {
  server.handleClient();
}  
```
**server.handleClient():** Esta función escucha continuamente si hay nuevas solicitudes HTTP de clientes  (navegadores web). Si hay una solicitud, la función correspondiente (handleRoot, handleLedOn, o handleLedOff) será llamada dependiendo de la ruta solicitada.  

### Flujo General
- El ESP32 se conecta a la red Wi-Fi con las credenciales que proporcionaste.
- El servidor web se inicializa en el puerto 80 y queda a la espera de solicitudes.
- Al acceder desde un navegador a la dirección IP del ESP32, se carga una página con dos botones para encender y apagar el LED.
- Al hacer clic en Encender LED, el servidor web ejecuta la función que enciende el LED y muestra una confirmación en la página.
- Al hacer clic en Apagar LED, el servidor apaga el LED y también muestra una confirmación.  

### 3- Prueba de funcionamiento:
- Acceder a la página web alojada por el ESP32 desde un navegador.
- Interactuar con los botones y observar el comportamiento del LED.  

## Herramientas externas: 
- Un navegador web
- El led integrado en la placa ESP32  

## Recomendaciones
- Mejorar la interfaz de la página web para obtener una experiencia mas interactiva.    

Para mejorar la interfaz de la página web, se propone realizar un recuadro centrado en la pagina con el titulo LED CONTROL y los dos botones de control dentro del recuadro y en colores, cambiando la funcion handleroot().

```cpp
 
void handleRoot() {
  String html = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<style>"
    "body { display: flex; justify-content: center; align-items: center; height: 100vh; font-family: Arial, sans-serif; margin: 0; }"
    ".container { text-align: center; padding: 20px; border: 2px solid #000; border-radius: 10px; background-color: #f9f9f9; width: 300px; }"
    "h1 { font-size: 24px; margin-bottom: 20px; }"
    "button { width: 100%; padding: 15px; margin: 10px 0; font-size: 18px; border: none; border-radius: 5px; cursor: pointer; }"
    "button:hover { background-color: #ddd; }"
    ".on { background-color: #4CAF50; color: white; }"
    ".off { background-color: #f44336; color: white; }"
    "</style>"
    "</head>"
    "<body>"
    "<div class=\"container\">"
    "<h1>LED CONTROL</h1>"
    "<a href=\"/on\"><button class=\"on\">Encender LED</button></a>"
    "<a href=\"/off\"><button class=\"off\">Apagar LED</button></a>"
    "</div>"
    "</body>"
    "</html>";
  
  server.send(200, "text/html", html);
}
```  
## Explicación del código:
### Estructura HTML:
- `<div class="container">`: Este div contiene todo el contenido de la página (título y botones). La clase  container" define su estilo para centrarlo en la página.
- `<h1>LED CONTROL</h1>`: Este es el título que aparecerá arriba del recuadro.
- Botones: Cada botón está dentro de un enlace `<a>`, para que al hacer clic en él, se envíe la petición al servidor para encender o apagar el LED.  

### Estilos `CSS`:
- Centrado vertical y horizontal: Usamos las propiedades de flexbox `(display: flex, justify-content: center, align-items: center)` para centrar el recuadro en el medio de la página.
- `container`: Define un recuadro con bordes, un fondo de color claro y esquinas redondeadas para contener el título y los botones.
- Botones: Tienen un tamaño uniforme, con bordes redondeados y un efecto de hover para cambiar el color al pasar el mouse por encima. Los botones están estilizados con diferentes colores para encender y apagar el LED:
  - Encender: Fondo verde con texto blanco (class="on").
  - Apagar: Fondo rojo con texto blanco (class="off").

### Resultado esperado:
Observaremos un recuadro centrado con el título LED CONTROL en la parte superior.
Dentro del recuadro, habrá dos botones alineados verticalmente: uno para Encender LED (verde) y otro para Apagar LED (rojo).
El diseño se adaptará a pantallas pequeñas gracias a la etiqueta `<meta name="viewport">`, asegurando que se vea bien en dispositivos móviles también.
