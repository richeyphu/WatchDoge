/*!
 * [ WatchDoge - WiFi Gateway Module ]
 * A Arduino Sketch for ESP32
 */

// Check if the board is ESP32
#ifndef ESP32
#pragma message(THIS SKETCH IS FOR ESP32 ONLY !)
#error Please select ESP32 board.
#endif

// Include libraries
#include <BlynkSimpleEsp32.h>
#include <TridentTD_LineNotify.h>
#include "conf.h"

// Declare GPIO pins
const int PIR_IN = 32;
const int BLYNK_OUT = 33;

// Declare credentials
const char SSID[] = WIFI_SSID;
const char PASS[] = WIFI_PASSWORD;
const char AUTH[] = BLYNK_AUTH_TOKEN;

// Declare state variables
int pirState = 0;
int blynkState = 0;

// Declare objects
BlynkTimer timer;

// Setup code, run once
void setup()
{
  // Start serial monitor
  Serial.begin(115200);

  // Start Blynk
  Blynk.begin(AUTH, SSID, PASS);
  timer.setInterval(1000L, timerEvent);

  // Set Line Notify token
  LINE.setToken(LINE_TOKEN);

  // Set GPIO pin modes
  pinMode(PIR_IN, INPUT);
  pinMode(BLYNK_OUT, OUTPUT);
}

// Main code, run repeatedly
void loop()
{
  // Run Blynk
  Blynk.run();
  timer.run();

  // Get PIR sensor state
  pirState = digitalRead(PIR_IN);

  printState();

  // Check if PIR sensor detects
  if (pirState == 1 && blynkState == 1)
  {
    // Send notification to Line
    LINE.notify("Intruder detected!");
    Serial.println("Line notification sent!");
  }

  Serial.println("------------------------------");
}

// Blynk timer event
void timerEvent()
{
}

void printState()
{
  Serial.print("PIR: ");
  Serial.println(pirState);
  Serial.print("BLYNK: ");
  Serial.println(blynkState);
}

// Blynk virtual pin event
BLYNK_WRITE(V0)
{
  if (param.asInt())
  {
    blynkState = 1;
    digitalWrite(BLYNK_OUT, LOW);
  }
  else
  {
    blynkState = 0;
    digitalWrite(BLYNK_OUT, HIGH);
  }
}
