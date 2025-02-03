#include "api.h"
#include "slidingwindow.h"

#define moveSpeed 60
#define SteerSpeed 50
#define distanceThreshold 10
#define normalTurnTime 1000
#define UTurnTime 2 * normalTurnTime
#define endCleaningTurnTime 100

RGBv colours;
int histlen = 5;
int colhist[5] = {-1, -1, -1, -1, -1};

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
    long feedbackDistance = getDistanceCM(); // declared and intialize the latest distance var
    turnStartTime = millis();                // restart the timer
    setMotors(0, 0);
    getRGB(&rgbValue);
    int col = getMaximum(rgbValue.redPW, rgbValue.bluePW, rgbValue.greenPW);
    addnew(colhist, col, histlen); //Add new colour measurement to colour history
    int colavg = colouraverage(colhist, histlen); //Get the average colour of the last 5 measurements
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
