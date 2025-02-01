#include "api.h"

typedef struct {
	int redPW;
  	int bluePW;
  	int greenPW;
} RGBv;

// Structure for Color Pulse Width Measurements
void getRGB(RGBv *rgb) {

	rgb->redPW = getRedPW();
	delay(50);

	rgb->greenPW = getGreenPW();
	delay(50);

	rgb->bluePW = getBluePW();
  delay(50);
}

int getDelta(RGBv *rgb,int origRed,int origBlue, int origGreen) {
  return (abs(rgb->redPW - origRed) + abs(rgb->bluePW - origBlue) + abs(rgb->greenPW - origGreen));
}

int getMinimum(int red, int blue, int green) { // give value
  if(red >= 110 && blue >= 110 && green >= 110){
    return -1; // black
  }
  // get current state based on which color value is the lowest
  if (min(red, blue) == red && min(red, green) == red) {
    return 0; // red
  } else if (min(blue, red) == blue && min(blue, green) == blue) {
    return 1; // blue
  } else {
    return 2; // green
  }
}
