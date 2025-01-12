#include <FastLED.h>
#include "Rotary.h"

#define ROTARY_PIN1 4
#define ROTARY_PIN2 5
#define DATA_PIN 3
#define NUM_LEDS 8

CRGB leds[NUM_LEDS];
Rotary r = Rotary(ROTARY_PIN1, ROTARY_PIN2);

int currentLedIndex = 0;

void setup() {
  // Initialize LED Strip
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  
  // Initialize Rotary Encoder Callbacks
  r.setChangedHandler(rotaryChanged);
  r.setLeftRotationHandler(rotaryLeft);
  r.setRightRotationHandler(rotaryRight);
  
  // Initialize all LEDs to off
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Process rotary encoder events
  r.loop();
}

// Callback for overall position change
void rotaryChanged(Rotary& r) {
  // You can add additional logic here if needed
}

// Callback for left rotation (counter-clockwise)
void rotaryLeft(Rotary& r) {
  // Move LED index backwards
  currentLedIndex = (currentLedIndex - 1 + NUM_LEDS) % NUM_LEDS;
  
  // Update LED strip
  updateLedStrip();
}

// Callback for right rotation (clockwise)
void rotaryRight(Rotary& r) {
  // Move LED index forwards
  currentLedIndex = (currentLedIndex + 1) % NUM_LEDS;
  
  // Update LED strip
  updateLedStrip();
}

// Helper function to update LED strip
void updateLedStrip() {
  // Turn off all LEDs
  FastLED.clear();
  
  // Turn on the current LED with a distinct color
  // Turn on the current LED with a distinct color
    switch(currentLedIndex) {
      case 0: leds[currentLedIndex] = CRGB::Red; break;
      case 1: leds[currentLedIndex] = CRGB::Red; break;
      case 2: leds[currentLedIndex] = CRGB::Red; break;
      case 3: leds[currentLedIndex] = CRGB::Red; break;
      case 4: leds[currentLedIndex] = CRGB::Red; break;
      case 5: leds[currentLedIndex] = CRGB::Red; break;
      case 6: leds[currentLedIndex] = CRGB::Red; break;
      case 7: leds[currentLedIndex] = CRGB::Red; break;
    }
  
  // Update the LED strip
  FastLED.show();
}
  