#include "rgb.h"
#include "motor.h"

RGBv rgbValue;

// States: 0 = red, 1 = blue, 2 = green, 3 = black (starting state)
int currentState = 3;
int previousState = 3;
int liveReading = 3;

// Counter to track progress through the rings
int ringCounter = 5;

// Original color reference values
int origRed;
int origBlue;
int origGreen;

// Threshold to detect entry into the circle
int enterCircleThreshold = 200;
bool enteredCircle = false;

int rotationSpeedBonus = 5;
int rotationSpeedIncrement = 5;

int cruiseSpeed = 100;
int rotateSpeed = 70;

void setup() {
    // Initialize color sensor pins
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Initialize motor pins
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(EN_B, OUTPUT);

    myServo.attach(5);

    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    pinMode(sensorOut, INPUT);

    getRGB(&rgbValue);
	origRed = rgbValue.redPW;
	origBlue = rgbValue.bluePW;
	origGreen = rgbValue.greenPW;
    Serial.begin(9600);
}

void loop() {
    // Spiral search to enter the circle
    while (!enteredCircle) {
        setMotors(255, 90 + rotationSpeedBonus);
        rotationSpeedBonus = min(200, rotationSpeedBonus + rotationSpeedIncrement);

        getRGB(&rgbValue);
        int delta = getDelta(&rgbValue, origRed, origBlue, origGreen);
        if (delta > enterCircleThreshold) {
            enteredCircle = true;
            Serial.println("Entered Circle");
			setMotors(0, 0); // Stop
        	delay(500);
        }
    }

	// Get the live reading
    getRGB(&rgbValue);
    liveReading = getMinimum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);

    // Cruise mode
    setMotors(cruiseSpeed, cruiseSpeed);

    // Correct if accidentally steps out
    if (liveReading == previousState) {
        setMotors(0, 0); // Stop
        delay(500);
        setMotors(rotateSpeed, 0); // Rotate in place

        while (liveReading == previousState) {
			getRGB(&rgbValue);
  		  	liveReading = getMinimum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);
        }
        delay(50); // Delay to let it face inwards instead of tangential 
		setMotors(0, 0); // Stop once corrected
    }

	// If the robot moves in as desired, keep moving straight, decrement counter, update previous state
	if (liveReading != previousState && liveReading != currentState){
		ringCounter = max(0, ringCounter - 1);
		previousState = currentState;
	}

	// Update the current state (happens every loop regardless of what happens)
	currentState = liveReading;

	// Check if the robot has completed the circle
	if (ringCounter == 0) {
		setMotors(0, 0); // Stop
		delay(500);
		//Write code to back up a bit, later.
		release(); //Release flag
		break;
	}
}