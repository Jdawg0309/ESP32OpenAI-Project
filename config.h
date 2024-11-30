#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>
#include <TFT_eSPI.h>

// Wi-Fi credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// OpenAI API key and endpoint
extern const char* OPENAI_API_KEY;
extern const char* OPENAI_API_ENDPOINT;

// Function to connect to Wi-Fi
void connectToWiFi(TFT_eSPI &tft);

#endif
