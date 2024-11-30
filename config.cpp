#include "config.h"

// Define Wi-Fi credentials
const char* WIFI_SSID = "ZubaedWifi";  // Replace with your Wi-Fi SSID
const char* WIFI_PASSWORD = "Zubaed123";  // Replace with your Wi-Fi password
const char* OPENAI_API_KEY = "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";

//Define OpenAI API endpoint
const char* OPENAI_API_ENDPOINT = "https://api.openai.com/v1/chat/completions";

void connectToWiFi(TFT_eSPI &tft) {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  tft.setCursor(10, 90);
  tft.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }
  delay(1000);
  tft.setCursor(10, 120);
  if (WiFi.status() == WL_CONNECTED){
      tft.println("Wi-Fi Connected");
      tft.println("IP address: " + WiFi.localIP().toString());
      delay(1000);

  }

}
