#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED 9
#define PIXELS 144

Adafruit_NeoPixel strip(PIXELS, LED, NEO_GRB + NEO_KHZ800);

void setup() {
	pinMode(LED, OUTPUT);

	Serial.begin(9600);
	strip.begin();
}

const char saturation = 255;
const char rainbow_brightness = 100;
const char speed = 10;

uint32_t meteor_color = strip.Color(50, 0, 0);
const char meteor_length = 10;
const short meteor_constant = 65535 / (PIXELS + meteor_length);

unsigned short i = 0;

void loop() {
	// Rainbow
	strip.rainbow(i, 1, saturation, rainbow_brightness);

	// Meteor
	short local_constant = i / meteor_constant;
	for (int j = local_constant; j > local_constant - meteor_length; j--) {
		strip.setPixelColor(j, meteor_color);
	}

	strip.show();
	delay(speed);

	i += 256;
}
