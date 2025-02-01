#include "api.h"

typedef struct {
	int redPW;
  	int bluePW;
  	int greenPW;
} RGBv;

// Structure for Color Pulse Width Measurements
void getRGB(RGBv *rgb) {

	rgb->redPW = getRedPW();
	delay(200);

	rgb->greenPW = getGreenPW();
	delay(200);

	rgb->bluePW = getBluePW();

  delay(200);
}

int getDelta(RGBv *rgb,int origRed,int origBlue, int origGreen) {
  return (abs(rgb->redPW - origRed) + abs(rgb->bluePW - origBlue) + abs(rgb->greenPW - origGreen));
}