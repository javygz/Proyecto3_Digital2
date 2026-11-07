#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE

#include <Arduino.h>
#include <DabbleESP32.h>

// Procesa un mensaje completo de la Terminal de Dabble.
// En esta primera etapa solo confirma la recepcion del comando.
void procesarComando(String comando) {
    comando.trim();
    comando.toUpperCase();

    if (comando.length() == 0) {
        return;
    }

    if (comando == "L") {
        Serial.println("Solicitud de lectura recibida.");
        Terminal.println("RECIBIDO L");
    } else if (comando == "G") {
        Serial.println("Solicitud de guardado recibida.");
        Terminal.println("RECIBIDO G");
    } else {
        Serial.println("Comando desconocido.");
        Terminal.println("ERROR: envia L o G");
    }
}

// Lee el mensaje que Dabble ya recibio y decodifico.
void recibirBluetooth() {
    if (Terminal.available() > 0) {
        String comando = Terminal.readString();
        procesarComando(comando);
    }
}

void setup() {
    Serial.begin(115200);
    Dabble.begin("Licht_ESP32");

    Serial.println("ESP32 lista.");
    Serial.println("Envia L o G.");
}

void loop() {
    Dabble.processInput();
    recibirBluetooth();
    delay(5);
}
