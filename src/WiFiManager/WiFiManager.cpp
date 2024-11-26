#include "WiFiManager.h"

// Constructor
WiFiManager::WiFiManager(String ssid, String password, const char* ntpServer, int gmtOffsetSec, int daylightOffsetSec)
    : ssid(ssid), password(password), ntpServer(ntpServer), gmtOffsetSec(gmtOffsetSec), daylightOffsetSec(daylightOffsetSec) {}

// Initializes the WiFi connection.
long WiFiManager::init() {
    Serial.print("$ Connecting to Wi-Fi...");

    // Convert String to char* using temporary buffers.
    char ssidBuffer[ssid.length() + 1];
    char passwordBuffer[password.length() + 1];
    ssid.toCharArray(ssidBuffer, ssid.length() + 1);
    password.toCharArray(passwordBuffer, password.length() + 1);

    WiFi.begin(ssidBuffer, passwordBuffer);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("done.");
    Serial.print("$ WIFI: ");
    Serial.println(WiFi.localIP());

    long rssi = WiFi.RSSI();
    Serial.print("$ RSSI: ");
    Serial.println(rssi);

    return rssi;
}

// Checks if WiFi is connected.
bool WiFiManager::isConnected() const {
    Serial.print("$ Checking Wi-Fi connection...");
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("ok.");
        return true;
    } else {
        Serial.println("failed.");
        return false;
    }
}

// Returns the current RSSI value.
long WiFiManager::getRSSI() const {
    long rssi = WiFi.RSSI();
    Serial.print("$ Current RSSI: ");
    Serial.println(rssi);
    return rssi;
}

// Synchronizes and retrieves the current date.
String WiFiManager::getDate() {
    // Configure time using the stored NTP server and offsets.
    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("$ Failed to obtain date.");
        return "Error";
    }

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);

    Serial.print("$ Current date: ");
    Serial.println(buffer);

    return String(buffer);
}

// Synchronizes and retrieves the current date and time.
String WiFiManager::getDateTime() {
    // Configure time using the stored NTP server and offsets.
    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("$ Failed to obtain date and time.");
        return "Error";
    }

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    Serial.print("$ Current date and time: ");
    Serial.println(buffer);

    return String(buffer);
}

#include <ctime>

//
time_t WiFiManager::getRawDateTime() {
    // Configure time using the stored NTP server and offsets.
    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("$ Failed to obtain date.");
        return -1; // Return -1 to indicate an error.
    }

    // Convert the tm structure to a time_t value (Unix timestamp).
    time_t rawTime = mktime(&timeinfo);

    if (rawTime == -1) {
        Serial.println("$ Failed to convert date to time_t.");
        return -1;
    }

    Serial.print("$ Raw date/time (Unix timestamp): ");
    Serial.println(rawTime);

    return rawTime;
}


// Synchronizes and retrieves the current time.
String WiFiManager::getTime() {
    // Configure time using the stored NTP server and offsets.
    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("$ Failed to obtain time.");
        return "Error";
    }

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);

    Serial.print("$ Current time: ");
    Serial.println(buffer);

    return String(buffer);
}
