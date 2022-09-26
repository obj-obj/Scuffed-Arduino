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

// CONFIG //
const unsigned char rainbow_saturation = 255;
const unsigned char rainbow_brightness = 100;
const double rainbow_speed = 10;

uint32_t meteor_color = strip.Color(50, 0, 0);
const unsigned char meteor_length = 10;
const unsigned char meteor_pixels = PIXELS + meteor_length;
const double meteor_speed = 0.1;

// RUNTIME //
unsigned long time = 0;
unsigned long previous_time = 0;

unsigned short ri = 0;
short mi = 0;

void loop() {
	time = micros();
	const double delta_time = (time - previous_time);
	previous_time = time;

	ri += (rainbow_speed / 1000) * delta_time;
	mi += (meteor_speed / 1000) * delta_time;
	while (mi >= meteor_pixels) {
		mi -= meteor_pixels + meteor_length;
	}

	// Rainbow
	strip.rainbow(ri, 1, rainbow_saturation, rainbow_brightness);

	// Meteor
	for (int j = mi; j > mi - meteor_length; j--) {
		strip.setPixelColor(j, meteor_color);
	}

	strip.show();
}
