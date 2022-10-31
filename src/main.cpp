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
double rainbow_speed = 0.02;

const unsigned char meteor_length = 10;
const unsigned char meteor_pixels = PIXELS + meteor_length;
uint32_t meteor_color = strip.Color(100, 100, 100);
double meteor_speed = 0.0005;
double meteor_currspeed;

// RUNTIME //
unsigned long time = 0;
unsigned long previous_time = 0;
double delta_time;

unsigned short ri = 0;

void frame_setup() {
	time = micros();
	delta_time = (time - previous_time);
	previous_time = time;
}

void frame_end() {
	strip.show();
}

void rainbow() {
	ri += rainbow_speed * delta_time;
	strip.rainbow(ri, 1, 255, 100);
}

void chargeup_meteor(double ending_speed) {
	double mi = 0;
	while (mi < meteor_pixels) {
		frame_setup();
		rainbow();

		meteor_currspeed = meteor_speed * (((meteor_pixels - mi) / meteor_pixels) + ending_speed);

		mi += meteor_currspeed * delta_time;

		for (int i = mi; i > mi - meteor_length; i--) {
			strip.setPixelColor(i, meteor_color);
		}

		frame_end();
	}
}

void blocks() {
	int iterations = PIXELS / meteor_length;

	for (int i = 0; i <= iterations; i++) {
		int stop = PIXELS - (i * meteor_length);

		for (double j = 0; j < stop; j += meteor_speed * delta_time * 1.1) {
			frame_setup();
			rainbow();

			for (int l = PIXELS; l > stop; l--) {
				strip.setPixelColor(l, meteor_color);
			}

			for (int l = j; l > j - meteor_length; l--) {
				strip.setPixelColor(l, meteor_color);
			}

			frame_end();
		}
	}
}

void loop() {
	for (double i = 0.1; i < 1; i += 0.1) {
		chargeup_meteor(i);
	}
	blocks();

	/*
	// Serial parsing
	if (Serial.available() > 0) {
		String inp = Serial.readString();
		String cmd = inp.substring(0, 2);
		double val = (double)atoi(inp.substring(3).c_str());

		if (cmd == "rs") {
			rainbow_speed = val / 1000;
		}
		else if (cmd == "ms") {
			meteor_speed = val / 10000;
		}
	}
	*/
}
