#ifndef OLEDMANAGER_H
#define OLEDMANAGER_H

#include <U8g2lib.h>

class OLEDManager {
public:
    enum Mode { MODE_64x32, MODE_128x32, MODE_128x64 };

    OLEDManager(Mode mode);

    void init();
    void refresh();
    void drawBattery(int x, int y, int val);
    void drawHourglass(int x, int y, int val);
    void drawPie(int x, int y, int val);
    void drawWifi(int x, int y, long rssi);
    void textTime(int x, int y, const char* timeStr);
    void textPrompt();
    void textTH(int p, float t);

private:
    U8G2 *u8g2;
    Mode currentMode;

    int getRSSIVal(long rssi);

    // Static Battery Data
    static const uint8_t battery_l0[];
    static const uint8_t battery_l1[];
    static const uint8_t battery_l2[];
    static const uint8_t battery_r0[];
    static const uint8_t battery_r1[];
    static const uint8_t battery_r2[];

    // Static Circle Data
    static const uint8_t circle_l0[];
    static const uint8_t circle_l1[];
    static const uint8_t circle_l2[];
    static const uint8_t circle_r0[];
    static const uint8_t circle_r1[];
    static const uint8_t circle_r2[];

    // Static Wifi Data
    static const uint8_t wifi_l0[];
    static const uint8_t wifi_l1[];
    static const uint8_t wifi_l2[];
    static const uint8_t wifi_r0[];
    static const uint8_t wifi_r1[];
    static const uint8_t wifi_r2[];

};

#endif
