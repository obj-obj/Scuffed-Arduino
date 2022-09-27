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
const unsigned char rainbow_brightness = 255;
double rainbow_speed = 0.02;

const unsigned char meteor_length = 10;
const unsigned char meteor_pixels = PIXELS + meteor_length;
double meteor_speed = 0.0001;

// RUNTIME //
unsigned long time = 0;
unsigned long previous_time = 0;

unsigned short ri = 0;
double mi = 0;

void loop() {
	time = micros();
	const double delta_time = (time - previous_time);
	previous_time = time;

	ri += rainbow_speed * delta_time;
	mi += meteor_speed * delta_time;
	while (mi >= meteor_pixels) {
		mi -= meteor_pixels + meteor_length;
	}

	// Rainbow
	strip.rainbow(ri, 1, rainbow_saturation, rainbow_brightness);

	// Meteor
	for (int j = mi; j > mi - meteor_length; j--) {
		strip.setPixelColor(j, strip.Color(255, 0, 0));
	}

	strip.show();

	// Serial parsing
	if (Serial.available() > 0) {
		String inp = Serial.readString();

		if (inp.startsWith("rs")) {
			rainbow_speed = ((double)atoi(inp.substring(3).c_str())) / 1000;
		}
		else if (inp.startsWith("ms")) {
			meteor_speed = ((double)atoi(inp.substring(3).c_str())) / 100000;
		}
	}
}
