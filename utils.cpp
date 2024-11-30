#include "utils.h"
#include "config.h"
#include <ArduinoJson.h>

String parseResponse(String rawResponse) {
    int startIndex = rawResponse.indexOf("\"text\":\"") + 8;
    int endIndex = rawResponse.indexOf("\"", startIndex);
    if (startIndex > 0 && endIndex > startIndex) {
        return rawResponse.substring(startIndex, endIndex);
    }
    return "Invalid response.";
}

String sendToLLM(String input) {
    if (WiFi.status() != WL_CONNECTED) {
        return "Error: Wi-Fi not connected.";
    }

    HTTPClient http;

    // Use the chat-based API endpoint
    http.begin(OPENAI_API_ENDPOINT);  // Access endpoint from config.h
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(OPENAI_API_KEY));

    // Create the payload for the chat-based models
    String payload = "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"" + input + "\"}]}";
    Serial.println("Payload: " + payload);  // Debug: Print the payload

    // Send the POST request
    int httpResponseCode = http.POST(payload);
    Serial.println("HTTP Response Code: " + String(httpResponseCode));

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response: " + response);

        // Parse the response JSON
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, response);
        if (error) {
            Serial.println("JSON Parse Error: " + String(error.c_str()));
            http.end();
            return "Error: Failed to parse response.";
        }

        // Extract the content from the assistant's reply
        if (doc["choices"][0]["message"]["content"] != nullptr) {
            String completion = doc["choices"][0]["message"]["content"];
            completion.trim();
            http.end();
            return completion;
        } else {
            http.end();
            return "Error: Invalid response format.";
        }
    } else {
        String errorMessage = http.errorToString(httpResponseCode);
        Serial.println("HTTP Error: " + errorMessage);
        http.end();
        return "HTTP Error: " + errorMessage;
    }
}
