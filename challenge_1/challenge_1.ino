// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#include "api.h"
#include "rgb.h"

// Structure for Color Pulse Width Measurements
RGB rgbValues;

// 0 is red, 1 is blue, 2 is green, 3 is the starting state
int currentState = 3;
int previousState = 3;

// stores the original numbers for each color (default)
int origRed, origBlue, origGreen = -1;

// Delta used to detect entry into circle
int enterCircleThreshold = 20;
bool enteredCircle = false;

void setup() {
	//Color sensor pins
	//Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Pulse Width scaling to 20%s
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

  if (origRed == -1 && origBlue == -1 && origGreen == -1) {
    origRed = rgbValues.red;
    origBlue = rgbValues.bluePW;
    origGreen = rgbValues.greenPW;
  }

	// Setup Serial Monitor
	Serial.begin(9600);
}

void loop() {

  while (!enteredCircle) {
    getRGB(&rgbValues);
    int delta = rgbValues.getDelta();
    if (delta > enterCircleThreshold) {
      enteredCircle = true;
    }
  }

  // get current state (0 = red, 1 = blue, 2 = green)
  getRGB(&rgbValues);
  currentState = getMinimum(rgbValues.red, rgbValues.bluePW, rgbValues.greenPW);

  // Delay to stabilize sensor
	//Color Detection
	// Read Red Pulse Width
	redPW = getRedPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Green Pulse Width
	greenPW = getGreenPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Blue Pulse Width
	bluePW = getBluePW();
	// Delay to stabilize sensor
	delay(200);

	// Print output to Serial Monitor
	Serial.print("Red PW = ");
	Serial.print(rgbValues.red);
	Serial.print(" - Green PW = ");
	Serial.print(rgbValues.greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(rgbValues.bluePW);

  Serial.print("Current State = ");
  if (currentState == 0) {
    Serial.println("RED");
  } else if (currentState == 1) {
    Serial.println("BLUE");
  } else if (currentState == 2) {
    Serial.println("GREEN");
  } else {
    Serial.println("BROWN");
  }

  Serial.print("Previous State = ");

  if (previousState != currentState) {
    previousState = currentState;
    if (previousState == 0) {
      Serial.println("RED");
    } else if (previousState == 1) {
      Serial.println("BLUE");
    } else if (previousState == 2) {
      Serial.println("GREEN");
    } else {
      Serial.println("BROWN");
    }
  }

  delay(100);

}