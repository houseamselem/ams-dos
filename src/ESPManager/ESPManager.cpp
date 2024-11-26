#include "ESPManager.h"

// Constructor
ESPManager::ESPManager(Mode mode) : currentMode(mode) {
    initializePins();
    Serial.begin(115200);
}

// Helper to configure pins based on the selected mode
void ESPManager::initializePins() {
    switch (currentMode) {
        case D1R1:
            pins = {3, 1, 16, 5, 4, 14, 12, 13, 0, 2, 15};
            break;

        case D1R1MC:
            pins = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};
            break;

        case ESP01S:
            pins = {0, 255, 2, 255, 255, 255, 255, 255, 255, 255, 255}; // Unused pins set to 255
            break;
    }

    // Set all pins as INPUT/OUTPUT as necessary
    pinMode(pins.D0, INPUT);
    pinMode(pins.D1, INPUT);
    pinMode(pins.D2, INPUT);
    pinMode(pins.D3, INPUT);
    pinMode(pins.D4, INPUT);
    pinMode(pins.D5, INPUT);
    pinMode(pins.D6, INPUT);
    pinMode(pins.D7, INPUT);
    pinMode(pins.D8, INPUT);
}

// Example method implementations
int ESPManager::add(int a, int b) {
    return a + b;
}

void ESPManager::aRead() {
    Serial.println("A0");
    Serial.println(String(analogRead(0)));
}

void ESPManager::dRead() {
    Serial.println("Digital Pins Reading:");
    Serial.print("D0: ");
    Serial.println(digitalRead(pins.D0));
    // Add other pins as needed...
}

void ESPManager::ledBlink(int pin, byte repeat, int interval, bool logic) {
    for (int i = 0; i < repeat; i++) {
        digitalWrite(pin, logic ? HIGH : LOW);
        delay(interval);
        digitalWrite(pin, logic ? LOW : HIGH);
        delay(interval);
    }
}

void ESPManager::probe(int probeInterval) {
    aRead();
    dRead();
    delay(probeInterval);
}

void ESPManager::wait(uint8_t seconds) {
    delay(100);
    Serial.println("[IDLE] Waiting...");

    for (uint8_t t = seconds; t > 0; t--) {
        Serial.printf("[IDLE] Time left: %d seconds...\n", t);
        Serial.flush();
        delay(1000);
    }
}
