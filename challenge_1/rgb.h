#include "api.h"

typedef struct {
	int redPW;
  int bluePW;
  int greenPW;
} RGBv;

void getRGB(RGBv *rgb) {
  // Read Red Pulse Width
	rgb->redPW = getRedPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Green Pulse Width
	rgb->greenPW = getGreenPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Blue Pulse Width
	rgb->bluePW = getBluePW();

  delay(200);

}

int getDelta(RGBv *rgb,int origRed,int origBlue, int origGreen) {
  return (abs(rgb.redPW - origRed) + abs(rgb.bluePW - origBlue) + abs(rgb.greenPW - origGreen));
}+