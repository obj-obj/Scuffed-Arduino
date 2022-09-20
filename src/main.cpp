#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED 9
#define POWER 8
#define GROUND 10

Adafruit_NeoPixel strip(133, LED, NEO_GRB + NEO_KHZ800);

void setup() {
	strip.begin();
}

void loop() {
	strip.fill(strip.Color(255, 0, 0));
	strip.show();
	delay(100);
	strip.fill(strip.Color(0, 255, 0));
	strip.show();
	delay(100);
	strip.fill(strip.Color(0, 0, 255));
	delay(100);
	strip.show();
}
