#include <TFT_eSPI.h>  // Include the TFT_eSPI library
#include "config.h"
#include "utils.h"

// Initialize the TFT screen
TFT_eSPI tft = TFT_eSPI();

// Function to test the display
void testDisplay() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Display Test");

  delay(1000);

  tft.fillScreen(TFT_RED);    // Red screen
  delay(500);
  tft.fillScreen(TFT_GREEN);  // Green screen
  delay(500);
  tft.fillScreen(TFT_BLUE);   // Blue screen
  delay(500);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(10, 40);
  tft.println("Test Complete");
  delay(2000);
}

void setup() {
  Serial.begin(115200);  // Start the serial communication for debugging

  // Initialize the TFT display
  tft.init();
  tft.setRotation(1);

  // Run the display test
  testDisplay();

  // After the test, prepare the screen for the main program
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Initializing...");
  Serial.println("Initializing...");

  // Connect to Wi-Fi
  connectToWiFi(tft);

  // Display initialization complete
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(10, 10);
  tft.println("Ready!");
  Serial.println("Ready!");
}

void loop() {
  String userInput = "Explain gravity simply";

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(2);
  tft.println("User:");
  tft.setCursor(10, 60);
  tft.println(userInput);
  Serial.println("User Input: " + userInput);

  // Send user input to LLM
  String response = sendToLLM(userInput);

  // Display response on the screen
  tft.setCursor(10, 120);
  tft.setTextColor(TFT_YELLOW);
  tft.println("Response:");
  tft.setCursor(10, 150);
  tft.println(response);

  // Print response to Serial Monitor
  Serial.println("Response from LLM: " + response);

  delay(15000);
}
