#ifndef ESPMANAGER_H
#define ESPMANAGER_H

#include <Arduino.h>

class ESPManager {
public:
    // Available modes
    enum Mode {
        D1R1,
        D1R1MC, // D1 R1 Mini Clone
        ESP01S
    };

    // Constructor
    ESPManager(Mode mode);

    // Methods
    int add(int a, int b);
    void aRead();
    void dRead();
    void ledBlink(int pin, byte repeat, int interval, bool logic);
    void probe(int probeInterval);
    void wait(uint8_t seconds);

private:
    Mode currentMode;

    // Pin mappings based on mode
    struct Pins {
        uint8_t D0;
        uint8_t D1;
        uint8_t D2;
        uint8_t D3;
        uint8_t D4;
        uint8_t D5;
        uint8_t D6;
        uint8_t D7;
        uint8_t D8;
        uint8_t RX;
        uint8_t TX;
    };

    Pins pins;

    void initializePins(); // Helper to configure pins based on mode
};

#endif // ESPMANAGER_H
