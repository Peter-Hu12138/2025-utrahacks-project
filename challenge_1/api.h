#include "rgb.h"
#include "motor.h"

#define trigPin 13
#define echoPin 12

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

float getColor()
{
    return 0.0; // TODO should be changed
}

void setMotors(int leftMotorSpeed, int rightMotorSpeed)
{
    // TODO
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