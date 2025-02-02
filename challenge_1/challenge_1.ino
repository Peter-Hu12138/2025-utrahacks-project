#include "rgb.h"
#include "motor.h"
#include "slidingwindow.h"

RGBv rgbValue;

int histlen = 10;
int colhist[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

// States: 0 = red, 1 = blue, 2 = green, 3 = black (starting state)
int currentState = -1;
int previousState = -1;
int colavg = -1;

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

int cruiseSpeed = 70;
int rotateSpeed = 30;

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
    delay(50); // stop for a second to read the color properly
    getRGB(&rgbValue);
	origRed = rgbValue.redPW;
	origBlue = rgbValue.bluePW;
	origGreen = rgbValue.greenPW;
    Serial.begin(9600);
}

void loop() {
    // Spiral search to enter the circle
    while (!enteredCircle) {
        setMotors(60, 30 + rotationSpeedBonus);
        rotationSpeedBonus = min(50, rotationSpeedBonus + rotationSpeedIncrement);

        delay(5); // stop for a second to read the color properly
        getRGB(&rgbValue);
        int col = getMaximum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);
        addnew(colhist, col, histlen); //Add new colour measurement to colour history
        int colavg = colouraverage(colhist, histlen); //Get the average colour of the last 5 measurements
        delay(5);
        if (colavg != -1) {
            enteredCircle = true;
            Serial.println("Entered Circle");
            setMotors(0, 0); // Stop
            delay(500);
        }
    }

    // Get the live reading
    delay(5); // stop for a second to read the color properly
    getRGB(&rgbValue);
    int col = getMaximum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);
    addnew(colhist, col, histlen); //Add new colour measurement to colour history
    int colavg = colouraverage(colhist, histlen); //Get the average colour of the last 5 measurements
    Serial.print(colavg);
    // for(int i=0; i<histlen; i++){
    //   Serial.println(colhist[i]);
    // }

    // Cruise mode
    setMotors(cruiseSpeed, cruiseSpeed);
    // Correct if accidentally steps out
    if (colavg == previousState) {
        setMotors(0, 0); // Stop
        delay(500);
        setMotors(rotateSpeed, 0); // Rotate in place

        while (colavg == previousState) {
        delay(5); // stop for a second to read the color properly
        getRGB(&rgbValue);
  		  	colavg = getMaximum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);
        }
        delay(50); // Delay to let it face inwards instead of tangential 
        setMotors(0, 0); // Stop once corrected
    }

	// If the robot moves in as desired, keep moving straight, decrement counter, update previous state
	if (colavg != previousState && colavg != currentState){
		ringCounter = max(0, ringCounter - 1);
    Serial.print("Entered ring ");
    Serial.println(ringCounter);
		previousState = currentState;
	}

	// Update the current state (happens every loop regardless of what happens)
	currentState = colavg;

	// Check if the robot has completed the circle
	if (ringCounter == 0) {
		setMotors(0, 0); // Stop
		delay(500);
		//Write code to back up a bit, later.
		release(60); //Release flag; ANGLE TBD
		setMotors(0, 0);
    return;
	}
}