#include "api.h"
#include "rgb.h"

#define moveSpeed 60
#define SteerSpeed 50
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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  long distance = getDistanceCM();
  if (distance < distanceThreshold)
  {                                          // close to a wall, take the instruction
    long feedbackDistance = getDistanceCM(); // declared and intialize the latest distance var
    turnStartTime = millis();                // restart the timer
    setMotors(0, 0);
    delay(50); // stop for a second to read the color properly

    getRGB(&colors);
    int curr_color = getMinimum(colors.redPW, colors.bluePW, colors.greenPW)
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
      while (feedbackDistance <= distance * 1.5 + 4 || millis() - turnStartTime <= normalTurnTime))
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
