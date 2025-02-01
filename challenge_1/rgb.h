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

int getMinimum(int red, int blue, int green) {
  // get current state based on which color value is the lowest
  if (min(red, blue) == red && min(red, green) == red) {
    return 0;
  } else if (min(blue, red) == blue && min(blue, green) == blue) {
    return 1;
  } else {
    return 2;
  }
}