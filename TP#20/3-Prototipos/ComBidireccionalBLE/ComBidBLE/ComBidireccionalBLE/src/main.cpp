#include <Arduino.h>
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
