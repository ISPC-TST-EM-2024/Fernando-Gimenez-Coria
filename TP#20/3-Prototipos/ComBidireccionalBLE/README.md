![LOGO](../../rsc/visuales/LOGO.png)  
  
# - Práctica 3: Comunicación Bidireccional BLE - Control Remoto  
## Objetivo:
- Configurar el ESP32 como un servidor BLE que permita recibir comandos para controlar el LED integrado y enviar estado del mismo de vuelta al cliente.
## Librerías necesarias:
`BLEDevice.h`, `BLEServer.h`, `BLEUtils.h`, `BLECharacteristic.h`, que son librerías de Arduino para manejar BLE.
## Pasos a Seguir:
### 1- Configurar el servidor BLE:
- Configurar el ESP32 como un servidor BLE con dos características: una para recibir comandos de control (escritura) y otra para enviar el estado del LED (lectura).
### 2- Implementar control del LED:
- Implementar la lógica para cambiar el estado del LED según los comandos recibidos.
### 3- Implementar Lectura del Estado del LED:
- Implementar la lógica para leer el estado del LED y enviar este estado a los dispositivos conectados.
### 4- Prueba de Funcionamiento:
- Utilizar una aplicación BLE en un smartphone para enviar comandos y recibir el estado del LED.
- Observar como el LED cambia de estado según los comandos enviados.
### Herramientas: 
- Aplicación BLE en un smartphone, como "nRF connect".
### Recomendaciones:
Implementar mecanismos de seguridad, como la autenticación, si se usa en un entorno real.  

### Implementación  
```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLECharacteristic.h>

#define LED_PIN 2  // Pin del LED integrado

// UUID para identificar el servicio y las características
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID_WRITE "12345678-1234-1234-1234-123456789013"
#define CHARACTERISTIC_UUID_READ  "12345678-1234-1234-1234-123456789014"

// Características globales
BLECharacteristic *pCharacteristicWrite;
BLECharacteristic *pCharacteristicRead;

bool ledState = false;  // Estado del LED

// Clase que maneja la recepción de datos en la característica de escritura
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print("Comando recibido: ");
            for (int i = 0; i < value.length(); i++) {
                Serial.print(value[i]);
            }
            Serial.println();

            // Si recibe "1", enciende el LED, si recibe "0", lo apaga
            if (value == "1") {
                digitalWrite(LED_PIN, HIGH);
                ledState = true;
            } else if (value == "0") {
                digitalWrite(LED_PIN, LOW);
                ledState = false;
            }

            // Actualiza el estado del LED en la característica de lectura
            pCharacteristicRead->setValue(ledState ? "1" : "0");
        }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Configura el dispositivo como servidor BLE
  BLEDevice::init("ESP32_LED_Control"); // Nombre del dispositivo
  BLEServer *pServer = BLEDevice::createServer();

  // Crea el servicio BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Crea la característica para escribir (control del LED)
  pCharacteristicWrite = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_WRITE,
                          BLECharacteristic::PROPERTY_WRITE
                        );
  pCharacteristicWrite->setCallbacks(new MyCallbacks());

  // Crea la característica para leer (estado del LED)
  pCharacteristicRead = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_READ,
                          BLECharacteristic::PROPERTY_READ
                        );
  pCharacteristicRead->setValue("0");  // Estado inicial del LED apagado

  // Inicia el servicio y comienza a anunciar el servidor
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
  
  Serial.println("Servidor BLE iniciado");
}

void loop() {
  // No se necesita código adicional aquí, ya que todo se maneja por callbacks.
}

```  
## Explicación del codigo   

### 1. Librerías BLE
```cpp

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLECharacteristic.h>  
```
Estas librerías son fundamentales para configurar la funcionalidad BLE del ESP32:

`BLEDevice.h`: Controla la configuración y gestión del dispositivo BLE.
`BLEServer.h`: Se utiliza para configurar el ESP32 como servidor BLE.
`BLEUtils.h`: Proporciona utilidades adicionales relacionadas con BLE.
`BLECharacteristic.h`: Permite crear características BLE que el cliente puede leer o escribir, según sea necesario.  

### 2. Definición del pin del LED y UUIDs
```cpp
 
#define LED_PIN 2
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID_WRITE "12345678-1234-1234-1234-123456789013"
#define CHARACTERISTIC_UUID_READ "12345678-1234-1234-1234-123456789014"  
```
  
`LED_PIN`: Define el pin donde está conectado el LED en el ESP32 (en este caso, es el LED integrado en el pin 2).
`SERVICE_UUID`: Este UUID identifica el servicio que el ESP32 ofrecerá. Un servicio BLE agrupa características relacionadas. En este caso, estamos creando un servicio para controlar y monitorear el LED.
`CHARACTERISTIC_UUID_WRITE y CHARACTERISTIC_UUID_READ`: Estos UUIDs identifican las dos características que definimos para este servicio:  

- `CHARACTERISTIC_UUID_WRITE`: Permite que un cliente (por ejemplo, un smartphone) envíe comandos de control (escritura) al ESP32.
- `CHARACTERISTIC_UUID_READ`: Permite que el cliente lea el estado actual del LED (lectura).  

### 3. Variables Globales
```cpp
 
BLECharacteristic *pCharacteristicWrite;
BLECharacteristic *pCharacteristicRead;
bool ledState = false;  
```  

`pCharacteristicWrite` y `pCharacteristicRead`: Estas variables apuntan a las características que usaremos para escribir comandos al ESP32 y leer el estado del LED.
`ledState`: Variable booleana que guarda el estado del LED (encendido o apagado). Esto será útil para enviar el estado al cliente cuando se solicite.  

### 4. Clase para Manejar los Comandos (MyCallbacks)
```cpp
 
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print("Comando recibido: ");
            for (int i = 0; i < value.length(); i++) {
                Serial.print(value[i]);
            }
            Serial.println();
            
            if (value == "1") {
                digitalWrite(LED_PIN, HIGH);
                ledState = true;
            } else if (value == "0") {
                digitalWrite(LED_PIN, LOW);
                ledState = false;
            }

            pCharacteristicRead->setValue(ledState ? "1" : "0");
        }
    }
};  
```
`MyCallbacks`: Es una clase derivada de BLECharacteristicCallbacks que define el comportamiento que ocurre cuando el cliente escribe datos en la característica.
`onWrite()`: Esta función se llama cuando el cliente escribe algo en la característica de escritura. La lógica dentro de esta función controla el LED:
`Recibir el valor`: El valor que recibe el ESP32 es un string (por ejemplo, "1" o "0").
`Encender/Apagar LED`: Si el valor es "1", enciende el LED. Si es "0", lo apaga.
`Actualizar la característica de lectura`: Después de cambiar el estado del LED, actualiza el valor de la característica de lectura para reflejar si el LED está encendido o apagado (enviando "1" o "0").  

### 5. Función setup()
```cpp
 
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Configura el dispositivo como servidor BLE
  BLEDevice::init("ESP32_LED_Control");
  BLEServer *pServer = BLEDevice::createServer();

  // Crea el servicio BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Crea la característica para escribir (control del LED)
  pCharacteristicWrite = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_WRITE,
                          BLECharacteristic::PROPERTY_WRITE
                        );
  pCharacteristicWrite->setCallbacks(new MyCallbacks());

  // Crea la característica para leer (estado del LED)
  pCharacteristicRead = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_READ,
                          BLECharacteristic::PROPERTY_READ
                        );
  pCharacteristicRead->setValue("0");

  // Inicia el servicio y comienza a anunciar el servidor
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
  
  Serial.println("Servidor BLE iniciado");
}  
```
`Serial.begin(115200)`: Inicia la comunicación serial para que puedas ver los mensajes de depuración en el monitor serial.
`pinMode(LED_PIN, OUTPUT)`: Configura el pin del LED como una salida.
`BLEDevice::init("ESP32_LED_Control")`: Inicializa el ESP32 como un dispositivo BLE con el nombre "ESP32_LED_Control", que será visible desde un smartphone.
`BLEServer *pServer = BLEDevice::createServer()`: Crea un servidor BLE en el ESP32.
`pService->createService(SERVICE_UUID)`: Crea un servicio con el UUID especificado.  

## Características:
`pCharacteristicWrite`: Se define una característica que permite al cliente escribir datos (comandos para encender/apagar el LED). Se asigna el callback MyCallbacks para manejar las escrituras.
`pCharacteristicRead`: Se define una característica de solo lectura, que se inicializa con el valor "0" (LED apagado).
`pService->start()`: Inicia el servicio BLE.
`BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();`: Comienza a anunciar el dispositivo BLE, haciéndolo visible para los clientes cercanos (por ejemplo, un smartphone con una aplicación BLE).
`Serial.println("Servidor BLE iniciado")`: Muestra un mensaje en el monitor serial indicando que el servidor BLE ha sido iniciado correctamente.
### 6. Función loop()
```cpp
 
void loop() {
  // No se necesita código adicional aquí, ya que todo se maneja por callbacks.
}  
```
El `loop()` está vacío porque el servidor BLE y los callbacks gestionan la comunicación automáticamente. No se necesita escribir código adicional en el loop().
## Resumen de cómo funciona el código:
### Servidor BLE:
El ESP32 se configura como un servidor BLE que puede aceptar conexiones desde dispositivos BLE como un smartphone.
### Control del LED:
Un cliente puede enviar un comando "1" para encender el LED o "0" para apagarlo, usando la característica de escritura. El LED cambia de estado de inmediato según el valor recibido.
### Lectura del estado del LED:
El cliente puede leer la característica de estado del LED para saber si está encendido o apagado (devolverá "1" si está encendido y "0" si está apagado).
### Aplicación en el mundo real:
Se puede usar una aplicación BLE como nRF Connect para probar el código. Conectarse al ESP32, buscar las características BLE y enviar los comandos adecuados para controlar el LED y leer su estado.  

## Prueba de Funcionamiento
### Conexión desde un smartphone:

- Usar una aplicación como nRF Connect para escanear dispositivos BLE.
- Conectarse al dispositivo con el nombre "ESP32_LED_Control":  

    Se encontraran dos características:  

- Una para escribir (donde puedes enviar "1" o "0" para controlar el LED).
- Otra para leer (donde puedes leer el estado actual del LED).  

### Interacción:

Enviar "1" para encender el LED y "0" para apagarlo.  

Observar el estado del LED en la característica de lectura.  
  
## Mejoras  
Una posible mejora es implementar notificaciones en la característica de lectura y hacer que el cliente reciba actualizaciones automáticas cuando el estado del LED cambie, para esto es necesario habilitar las notificaciones BLE en el servidor ESP32.   
De esta manera, cada vez que el LED cambie de estado, el servidor enviará automáticamente una notificación al cliente sin necesidad de que este tenga que solicitar continuamente el estado.

A continuación modificamos el codigo original:

### 1. Habilitar las notificaciones en la característica de lectura:
En el código original, debemos modificar la creación de la característica de lectura para que soporte notificaciones, y luego enviar una notificación cada vez que cambie el estado del LED.

### Código actualizado:
```cpp
 
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLECharacteristic.h>

#define LED_PIN 2
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID_WRITE "12345678-1234-1234-1234-123456789013"
#define CHARACTERISTIC_UUID_READ "12345678-1234-1234-1234-123456789014"

BLECharacteristic *pCharacteristicWrite;
BLECharacteristic *pCharacteristicRead;
bool ledState = false;

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print("Comando recibido: ");
            for (int i = 0; i < value.length(); i++) {
                Serial.print(value[i]);
            }
            Serial.println();
            
            // Controlar el LED basado en el comando recibido
            if (value == "1") {
                digitalWrite(LED_PIN, HIGH);
                ledState = true;
            } else if (value == "0") {
                digitalWrite(LED_PIN, LOW);
                ledState = false;
            }

            // Actualizar el estado de la característica de lectura y enviar notificación
            pCharacteristicRead->setValue(ledState ? "1" : "0");
            pCharacteristicRead->notify();  // Enviar notificación al cliente
        }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Configura el dispositivo como servidor BLE
  BLEDevice::init("ESP32_LED_Control");
  BLEServer *pServer = BLEDevice::createServer();

  // Crea el servicio BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Crea la característica para escribir (control del LED)
  pCharacteristicWrite = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_WRITE,
                          BLECharacteristic::PROPERTY_WRITE
                        );
  pCharacteristicWrite->setCallbacks(new MyCallbacks());

  // Crea la característica para leer (estado del LED) con notificaciones
  pCharacteristicRead = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_READ,
                          BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                        );
  pCharacteristicRead->setValue("0");  // Estado inicial (LED apagado)

  // Inicia el servicio y comienza a anunciar el servidor
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
  
  Serial.println("Servidor BLE iniciado");
}

void loop() {
  // No se necesita código adicional aquí, ya que todo se maneja por callbacks.
}  
```  

## Explicación de los cambios:
### `PROPERTY_NOTIFY` en la característica de lectura:

En la parte donde creamos la característica de lectura, ahora agregamos el flag `BLECharacteristic::PROPERTY_NOTIFY` para habilitar la funcionalidad de notificaciones.
Esto permite que el servidor envíe actualizaciones automáticas al cliente cada vez que el valor de esta característica cambie.  

```cpp
 
pCharacteristicRead = pService->createCharacteristic(
                         CHARACTERISTIC_UUID_READ,
                         BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                       );  
```
  
### Enviar una notificación:

En la función `onWrite()`, después de cambiar el estado del LED y actualizar el valor de la característica de lectura, se llama al método `notify()` para enviar una notificación al cliente.
```cpp
 
pCharacteristicRead->notify();  // Enviar notificación al cliente  
```  

Esto hará que cualquier cliente conectado que esté suscrito a las notificaciones reciba una actualización automática del nuevo estado del LED.

## 3. Cómo funciona en el cliente:  

- Cuando un cliente BLE (como una aplicación de smartphone, por ejemplo, nRF Connect) se conecta al ESP32, debe suscribirse a las notificaciones de la característica de lectura para recibir actualizaciones.
 -Una vez que se haya suscrito, cada vez que el estado del LED cambie (al recibir un comando "1" o "0"), el ESP32 enviará una notificación al cliente con el nuevo estado ("1" si el LED está encendido y "0" si está apagado).  

## 4. Prueba en la app nRF Connect:
- Abrir la app nRF Connect en tu smartphone.
- Conectarse al ESP32 y buscar el servicio que contiene las características.
- En la característica de lectura (estado del LED), selecciona "Enable Notifications".  

Cada vez que enviemos un comando de encendido/apagado al ESP32, veremos que la app recibe una notificación con el estado actualizado del LED.  

## Resumen:
Al habilitar las notificaciones, el ESP32 puede informar automáticamente al cliente BLE sobre cualquier cambio en el estado del LED, sin que el cliente tenga que solicitarlo constantemente. Esto mejora la eficiencia de la comunicación BLE, ya que el cliente recibe actualizaciones en tiempo real solo cuando hay cambios.