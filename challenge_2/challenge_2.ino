#include "api.h"

#define moveSpeed 70
#define SteerSpeed 70
#define distanceThreshold 10
#define normalTurnTime 1000
#define UTurnTime 2 * normalTurnTime
#define endCleaningTurnTime 100

void moveForward()
{
  setMotors(moveSpeed, moveSpeed);
}

void moveBackward()
{
  setMotors(-moveSpeed, -moveSpeed);
}

void turnLeft()
{
  setMotors(SteerSpeed, -SteerSpeed); // might use tuning on the best speed
}

void turnRight()
{
  setMotors(-SteerSpeed, SteerSpeed);
}

void stopMotors()
{
  setMotors(0, 0);
}

unsigned long turnStartTime = 0;
RGBv colors;

void setup()
{
  Serial.begin(9600);
  ultrasonicSetup();
  motorSetup();
  colorSensorSetup();
}

void loop()
{
  float distance = getDistanceCM();
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance < distanceThreshold)
  {                                          // close to a wall, take the instruction
    float feedbackDistance = getDistanceCM(); // declared and intialize the latest distance var
    turnStartTime = millis();                // restart the timer
    setMotors(0, 0);
    delay(50); // stop for a second to read the color properly

    getRGB(&colors);
    Serial.print("Red PW = ");
	Serial.print(colors.redPW);
	Serial.print(" - Green PW = ");
	Serial.print(colors.greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(colors.bluePW);
    int curr_color = getMinimum(colors.redPW, colors.bluePW, colors.greenPW);
    Serial.print("Color: ");
    Serial.println(curr_color);
    if (curr_color == 1)
    {
      // Turn left
      while (feedbackDistance <= distance * 1.5 + 4 || millis() - turnStartTime <= normalTurnTime)
      {
        feedbackDistance = getDistanceCM();
        turnLeft();
      }
      unsigned int temp = millis();
      while (millis() - temp <= endCleaningTurnTime)
      {
        turnLeft();
      }
    }
    else if (curr_color == 2)
    {
      // Turn right
      while (feedbackDistance <= distance * 1.5 + 4 || millis() - turnStartTime <= normalTurnTime)
      {
        feedbackDistance = getDistanceCM();
        turnRight();
      }
      unsigned int temp = millis();
      while (millis() - temp <= endCleaningTurnTime)
      {
        turnRight();
      }
    }
    else if (curr_color == 0)
    {
      // U-turn
      while (millis() - turnStartTime <= UTurnTime)
      {
        feedbackDistance = getDistanceCM();
        turnRight();
      }
      unsigned int temp = millis();
      while (millis() - temp <= endCleaningTurnTime)
      {
        turnRight();
      }
    }
    else if (curr_color == -1)
    {
      // go straight
      while (millis() - turnStartTime <= 100)
      {
        feedbackDistance = getDistanceCM();
        turnRight();
      }
    }
    else
    {
      // default
    }
    stopMotors();
    delay(50);
  }
  else
  {
    moveForward();
  }
}
