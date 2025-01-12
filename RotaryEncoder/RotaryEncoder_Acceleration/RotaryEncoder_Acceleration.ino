#include <FastLED.h>
#include "Rotary.h"

#define ROTARY_PIN1 5
#define ROTARY_PIN2 4
#define DATA_PIN 3
#define NUM_LEDS 8

CRGB leds[NUM_LEDS];
Rotary r = Rotary(ROTARY_PIN1, ROTARY_PIN2);

float currentLedIndex = 0;
float velocity = 0;
float acceleration = 0;

const float MAX_VELOCITY = 2.5;
const float ACCELERATION_FACTOR = 0.1;
const float FRICTION = 0.97;

int prevPosition = 0;
float prevLedIndex = 0;

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
  Serial.begin(115200);
}

void loop() {
  // Process rotary encoder events
  r.loop();

  // Update LED position based on velocity
  updateLedPosition();
}

// Callback for overall position change
void rotaryChanged(Rotary& r) {
  // You can add additional logic here if needed
  Serial.print(r.getIncrement());
  Serial.print(" \t ");
  Serial.print(r.getDirection());
  Serial.print(" \t ");
  Serial.println(r.getPosition());
  if ((int)(r.getPosition() / 20.0) != prevPosition) {
    acceleration += (r.getDirection() > 128) ? -ACCELERATION_FACTOR : ACCELERATION_FACTOR;
  }
  prevPosition = round(r.getPosition() / 20.0);
}

// Callback for left rotation (counter-clockwise)
void rotaryLeft(Rotary& r) {
  // Apply negative acceleration
  // acceleration -= ACCELERATION_FACTOR;
}

// Callback for right rotation (clockwise)
void rotaryRight(Rotary& r) {
  // Apply positive acceleration
  // acceleration += ACCELERATION_FACTOR;
}

// Update LED position with physics-like movement
void updateLedPosition() {
  // Apply velocity and acceleration
  velocity += acceleration;

  // Limit velocity
  velocity = constrain(velocity, -MAX_VELOCITY, MAX_VELOCITY);

  // Apply friction to slow down
  velocity *= FRICTION;

  // Update LED index
  currentLedIndex += velocity;

  // Wrap around the LED strip
  if (currentLedIndex >= NUM_LEDS) currentLedIndex = 0;
  if (currentLedIndex < 0) currentLedIndex = NUM_LEDS - 1;
  if (prevLedIndex != currentLedIndex) {
    // Turn off all LEDs
    FastLED.clear();

    // Turn on the current LED with a distinct color
    int ledIndex = (int)currentLedIndex;
    Serial.println(ledIndex);
    leds[ledIndex] = CRGB::Red;

    // Update the LED strip
    FastLED.show();
    prevLedIndex = currentLedIndex;
  }
  // Reset acceleration
  acceleration = 0;
}