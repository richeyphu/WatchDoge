/*!
 * [ WatchDoge - Dedicated Rickrolling Module ]
 * A Arduino Sketch for Uno
 */

// Check if the board is Arduino Uno
#ifndef ARDUINO_AVR_UNO
#pragma message(THIS SKETCH IS FOR ARDUINO UNO ONLY !)
#error Select Arduino Uno board.
#endif

// Include libraries
#include "rickroll.h"

// Declare peripheral pins
const int PIR = 8;
const int PIEZO = 7;
const int LED0 = LED_BUILTIN;
const int LED1 = 10;

// Declare PIR sensor state
int pirDetect = 0;

// Setup code, run once
void setup()
{
  pinMode(PIEZO, OUTPUT);
  pinMode(LED0, OUTPUT);

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
  pirDetect = digitalRead(PIR);
  Serial.print(" - sensor ");
  Serial.println(pirDetect);

  // Turn on LED1 if PIR sensor detects
  if (pirDetect == 1)
  {
    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }

  // play next step in song
  if (flag == true)
  {
    play();
  }
}

// Play a note based on current state
void play()
{
  // If PIR sensor is not detecting, stop playing song
  if (pirDetect == 0)
  {
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
