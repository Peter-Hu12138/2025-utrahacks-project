#include "rgb.h"
#include "motor.h"

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

int rotationSpeedBonus = 5;
int rotationSpeedIncrement = 5;'

int cruiseSpeed = 100;
int rotateSpeed = 70;

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



void updateliveReading() {
	// get current state (0 = red, 1 = blue, 2 = green, 3 = black)
	getRGB(&rgbValue);
	liveReading = getMinimum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW); //Live reading
	}

void boundaryCheck(){
	//If boundary is reached (we dont know which one)
	if (currentState != liveReading) {
		//If the robot accidentally moved outwards
		if (liveReading == previousState){
			//Stop, rotate until sensor sees the right color again before resuming
			}

		//If the robot approached inwards
		else{

		}
	// if current state has changed, then we have progressed one ring
	if (ringCounter >= 0) {
		ringCounter--;
	}
	}
}

void loop() {
	//While outside of the circle, rotate in a spiral of increasing radius
	while (!enteredCircle) {
		setMotors(255, 90+rotationSpeedBonus);
		if (rotationSpeedBonus + rotationSpeedIncrement < 200) {
			rotationSpeedBonus += rotationSpeedIncrement;
		}

		getRGB(&rgbValue);
		int delta = getDelta(&rgbValue, origRed, origBlue, origGreen);
		if (delta > enterCircleThreshold) {
		enteredCircle = true;
    Serial.println("Entered Circle");
		}

		delay(500);
		continue;
	}

	updateColourStates();



	//Write search mode behavior here

	//Cruise mode behavior
	setMotors(cruiseSpeed, cruiseSpeed);

	//When it accidentally steps out
	if (currentState == previousState) { 
		setMotors(0,0); //Stop before we stray further
		delay(500);
		setMotors(rotateSpeed,0); //Rotate on site
		while {
			updateColourStates();
			if (currentState != previousState) {
				setMotors(0,0);
				break;
			}
		}
	}


	delay(50);
}