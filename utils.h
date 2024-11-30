#ifndef UTILS_H
#define UTILS_H

#include <HTTPClient.h>

// Function to parse LLM response
String parseResponse(String rawResponse);

// Function to send input to LLM
String sendToLLM(String input);

#endif
