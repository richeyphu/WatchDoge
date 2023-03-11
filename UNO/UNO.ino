/*!
 * [ WatchDoge - Dedicated Rickrolling Module ]
 * A Arduino Sketch for Uno
 */

// Check if the board is Arduino Uno
#ifndef ARDUINO_AVR_UNO
#pragma message(THIS SKETCH IS FOR ARDUINO UNO ONLY !)
#error Please select Arduino Uno board.
#endif

// Include libraries
#include "rickroll.h"

// Declare GPIO pins
const int PIR = 8;
const int PIR_OUT = 4;
const int PIEZO = 7;
const int LED0 = LED_BUILTIN;
const int LED1 = 12;
const int BLYNK_IN = 2;

// Declare state variables
int pirState = 0;
int blynkState = 0;

// Setup code, run once
void setup()
{
  // Set GPIO pin modes
  pinMode(PIR, INPUT);
  pinMode(PIR_OUT, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(BLYNK_IN, INPUT);

  digitalWrite(LED0, LOW);
  Serial.begin(115200);
  flag = true;
  a = 4; // part index
  b = 0; // song index
  c = 0; // lyric index
}

// Main code, run repeatedly
void loop()
{
  // Get PIR sensor state
  pirState = digitalRead(PIR);
  // Get Blynk state
  blynkState = digitalRead(BLYNK_IN);

  printState();

  // Check if PIR sensor is detecting
  if (pirState == 1)
  {
    // Turn on LED if PIR sensor detects
    ledAlert(LED1);
    digitalWrite(PIR_OUT, HIGH);
  }
  else
  {
    // Turn off LED if PIR sensor does not detect
    digitalWrite(LED1, LOW);
    digitalWrite(PIR_OUT, LOW);
  }

  // Play next step in song
  if (flag == true)
  {
    play();
  }
}

void printState()
{
  Serial.print("- PIR: ");
  Serial.print(pirState);
  Serial.print(", BLYNK: ");
  Serial.println(blynkState);
}

void ledAlert(int led)
{
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
}

// Play a note based on current state
void play()
{
  // If PIR sensor is not detecting or getting Blynk signal
  if (pirState == 0 || blynkState == 1)
  {
    // Stop playing the song
    return;
  }

  int notelength;
  if (a == 1 || a == 2)
  {
    // intro
    notelength = beatlength * song1_intro_rhythmn[b];
    if (song1_intro_melody[b] > 0)
    {
      digitalWrite(LED0, HIGH);
      tone(PIEZO, song1_intro_melody[b], notelength);
    }
    b++;
    if (b >= sizeof(song1_intro_melody) / sizeof(int))
    {
      a++;
      b = 0;
      c = 0;
    }
  }
  else if (a == 3 || a == 5)
  {
    // verse
    notelength = beatlength * 2 * song1_verse1_rhythmn[b];
    if (song1_verse1_melody[b] > 0)
    {
      digitalWrite(LED0, HIGH);
      Serial.print(lyrics_verse1[c]);
      tone(PIEZO, song1_verse1_melody[b], notelength);
      c++;
    }
    b++;
    if (b >= sizeof(song1_verse1_melody) / sizeof(int))
    {
      a++;
      b = 0;
      c = 0;
    }
  }
  else if (a == 4 || a == 6)
  {
    // chorus
    notelength = beatlength * song1_chorus_rhythmn[b];
    if (song1_chorus_melody[b] > 0)
    {
      digitalWrite(LED0, HIGH);
      Serial.print(lyrics_chorus[c]);
      tone(PIEZO, song1_chorus_melody[b], notelength);
      c++;
    }
    b++;
    if (b >= sizeof(song1_chorus_melody) / sizeof(int))
    {
      Serial.println("");
      a++;
      b = 0;
      c = 0;
    }
  }
  delay(notelength);
  noTone(PIEZO);
  digitalWrite(LED0, LOW);
  delay(notelength * beatseparationconstant);
  if (a == 7)
  { // loop back around to beginning of song
    a = 1;
  }
}

/*
█▀▀▀▀▀█ ▀▀      █ █▀▀▀▀▀█
█ ███ █ █▄ ██▀▄▀  █ ███ █
█ ▀▀▀ █ ▀█▀▀▄▄ ▀  █ ▀▀▀ █
▀▀▀▀▀▀▀ ▀▄▀▄▀ ▀ █ ▀▀▀▀▀▀▀
▀▀▀▀▄ ▀▄▀▄  ▀ █ █▀ ▄▀▀▀▄▀
 ████ ▀█   █▀█▄▄▄▄███▄▄
  ▀ ▄█▀ ▄█▄ █▀ █▄▀███ ▀▀█
▄▀▄█▄ ▀▀▄▄  ▄▀▀ ██▄▄█ ▀▀▄
   ▀▀▀▀ ▄█  ██▄▀█▀▀▀█▀█▀█
█▀▀▀▀▀█   ▄ ▄▀▀ █ ▀ █ ▀█▀
█ ███ █ ▄█▀▄ ▄▄ ▀██▀██▄██
█ ▀▀▀ █ █  ██▄██ ▄▀ █ █▀
▀▀▀▀▀▀▀ ▀▀▀   ▀   ▀▀▀▀▀▀▀
*/
