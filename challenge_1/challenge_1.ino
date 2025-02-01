#include "rgb.h"
#include "hardware.h"

RGBv rgbValue;

// 0 is red, 1 is blue, 2 is green, 3 is black, the starting state
int currentState = 3;
int previousState = 3;
int tempState = 3;

// counter to check how far we've progressed in the circle
int ringCounter = 5;

// stores the original numbers for each color (default)
int origRed = -1;
int origBlue = -1;
int origGreen = -1;

// Delta used to detect entry into circle
int enterCircleThreshold = 200;
bool enteredCircle = false;

void setup() {
	//Initializing the color sensor pins as output
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	//Initializing the motor pins as output
	pinMode(EN_A, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(EN_B, OUTPUT);

	myServo.attach(5);

	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

	pinMode(sensorOut, INPUT);

	getRGB(&rgbValue);
	if (origRed == -1 && origBlue == -1 && origGreen == -1) {
		origRed = rgbValue.redPW;
		origBlue = rgbValue.bluePW;
		origGreen = rgbValue.greenPW;
	}

	Serial.begin(9600);
}

void loop() {

	while (!enteredCircle) {
		getRGB(&rgbValue);
		int delta = getDelta(&rgbValue, origRed, origBlue, origGreen);
		if (delta > enterCircleThreshold) {
		enteredCircle = true;
    Serial.println("Entered Circle");
		}
    Serial.println("Current State = BLACK");
    Serial.print("Red PW = ");
    Serial.print(origRed);
    Serial.print(" - Green PW = ");
    Serial.print(origGreen);
    Serial.print(" - Blue PW = ");
    Serial.println(origBlue);

    Serial.println("Current State = BLACK");
    Serial.print("Red PW = ");
    Serial.print(rgbValue.redPW);
    Serial.print(" - Green PW = ");
    Serial.print(rgbValue.greenPW);
    Serial.print(" - Blue PW = ");
    Serial.println(rgbValue.bluePW);
    continue;
	}

  delay(2000);

	// get current state (0 = red, 1 = blue, 2 = green, 3 = black)
	getRGB(&rgbValue);
  tempState = getMinimum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);

  // logic for changing previousState and currentState
  if (currentState != tempState) {
    previousState = currentState;
    currentState = tempState;
    // if current state has changed, then we have progressed one ring
    if (ringCounter >= 0) {
      ringCounter--;
    }
  }

  Serial.print("Ring Number = ");
  Serial.println(ringCounter);

	Serial.print("Red PW = ");
	Serial.print(rgbValue.redPW);
	Serial.print(" - Green PW = ");
	Serial.print(rgbValue.greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(rgbValue.bluePW);

	Serial.print("Current State = ");
	if (currentState == 0) {
		Serial.println("RED");
	} else if (currentState == 1) {
		Serial.println("BLUE");
	} else if (currentState == 2) {
		Serial.println("GREEN");
	} else {
		Serial.println("BLACK");
	}

	Serial.print("Previous State = ");

  if (previousState == 0) {
		Serial.println("RED");
		} else if (previousState == 1) {
		Serial.println("BLUE");
		} else if (previousState == 2) {
		Serial.println("GREEN");
		} else {
		Serial.println("BLACK");
	}

  delay(100);

}