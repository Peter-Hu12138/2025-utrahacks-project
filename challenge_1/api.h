#include <Arduino.h>
#include <string.h>  // Required for strcmp()

// Ultrasonic sensor
#define trigPin 13
#define echoPin 12

// Motor
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define EN_A 11
#define EN_B 10

float getColor()
{
    return 0.0; // TODO should be changed
}


float getDistanceCM() // CM
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = (duration / 2) / 29.1; // Convert to centimeters
    return distance;
}

void adjustServo()
{
    // TODO
}

float getServoAngle()
{
    return 0.0; // TODO
}

int getRedPW() {
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);

	return pulseIn(sensorOut, LOW);
}

int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

int getBluePW() {
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);

	return pulseIn(sensorOut, LOW);
}

// Convention: 1,3 LOW for forward; 2,4 LOW for backward
void move_one(int speed, const char* dir, int inPin1, int inPin2, int pwmPin) {
    if (strcmp(dir, "FWD") == 0) {  
        digitalWrite(inPin1, LOW);
        digitalWrite(inPin2, HIGH);
    } 
    else if (strcmp(dir, "REV") == 0) {  
        digitalWrite(inPin1, HIGH);
        digitalWrite(inPin2, LOW);
    }
    analogWrite(pwmPin, speed);
}

void setMotors(int leftSpeed, int rightSpeed) {
    const char* leftDir = (leftSpeed >= 0) ? "FWD" : "REV";
    const char* rightDir = (rightSpeed >= 0) ? "FWD" : "REV";
    move_one(abs(leftSpeed), leftDir, IN1, IN2, EN_A);
    move_one(abs(rightSpeed), rightDir, IN3, IN4, EN_B);
}

void stop() {
    move_one(0, "FWD", IN1, IN2, EN_A);
    move_one(0, "REV", IN3, IN4, EN_B);
}
