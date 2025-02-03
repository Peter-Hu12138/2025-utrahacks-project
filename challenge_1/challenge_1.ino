#include "rgb.h"
#include "motor.h"
#include "slidingwindow.h"

RGBv rgbValue;

int histlen = 5;
int colhist[5] = {-1, -1, -1, -1, -1};

// States: 0 = red, 1 = blue, 2 = green, 3 = black (starting state)
int currentState = -1;
int previousState = -1;
int colavg = -1;

// Counter to track progress through the rings
int ringCounter = 3;

// Threshold to detect entry into the circle
int enterCircleThreshold = 200;
bool enteredCircle = false;

int rotationSpeedBonus = 10;
int rotationSpeedIncrement = 5;

int cruiseSpeed = 80;
int rotateSpeed = 100;

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

    myServo.attach(A1);

    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    pinMode(sensorOut, INPUT);
    delay(50); // stop for a second to read the color properly
    Serial.begin(9600);

    grab();

    setMotors(60, 30);


}

void loop() {
    // Spiral search to enter the circle
    while (!enteredCircle) {
        setMotors(120, 20+ rotationSpeedBonus);
        rotationSpeedBonus = rotationSpeedBonus + 5;

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
    // for(int i=0; i<histlen; i++){
    //   Serial.println(colhist[i]);
    // }

    
    // Correct if accidentally steps out
    Serial.println(colavg);
    Serial.println(currentState);
    Serial.println(previousState);
    if (colavg == currentState){
      // Cruise mode
    
    setMotors(cruiseSpeed, cruiseSpeed);
    }
    if (colavg == previousState) {
        setMotors(0, 0); // Stop
        delay(50);
        setMotors(rotateSpeed, 0); // Rotate in place
        getRGB(&rgbValue);
        int col = getMaximum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);
        addnew(colhist, col, histlen); //Add new colour measurement to colour history
        int colavg = colouraverage(colhist, histlen); //Get the average colour of the last 5 measurements
        Serial.println(colavg);
        Serial.println(previousState);
        if(colavg != previousState){
          delay(300); // Delay to let it face inwards instead of tangential 
          setMotors(0, 0); // Stop once corrected
        }
    }

	// If the robot moves in as desired, keep moving straight, decrement counter, update previous state
	if (colavg != previousState && colavg != currentState){
		ringCounter = max(0, ringCounter - 1);
        Serial.print("Entered ring ");
        Serial.println(ringCounter);
		previousState = currentState;
    // Update the current state (happens every loop regardless of what happens)
	  currentState = colavg;
	}

	

	// Check if the robot has completed the circle
	if (ringCounter == 0) {
		setMotors(0, 0); // Stop
		delay(500);
		//Write code to back up a bit, later.
		release(90); //Release flag; ANGLE TBD
    delay(10);
		setMotors(0, 0);
    return;
	}
}