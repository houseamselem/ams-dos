#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <time.h>

class WiFiManager {
private:
    String ssid;
    String password;
    const char* ntpServer;
    int gmtOffsetSec;
    int daylightOffsetSec;

public:
    // Constructor to initialize the class with SSID, password, and NTP settings.
    WiFiManager(String ssid, String password, const char* ntpServer = "pool.ntp.org", int gmtOffsetSec = 0, int daylightOffsetSec = 0);

    // Initializes the WiFi connection.
    long init();

    // Checks if WiFi is connected.
    bool isConnected() const;

    // Returns the current RSSI value.
    long getRSSI() const;

    // Synchronizes and retrieves the current date & time.
    String getDate();
    String getDateTime();
    time_t getRawDateTime();
    String getTime();
};

#endif // WIFI_MANAGER_H
