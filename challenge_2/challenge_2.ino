#include "api.h"
#include "slidingwindow.h"

#define moveSpeed 70
#define SteerSpeed 60
#define distanceThreshold 5.0
#define normalTurnTime 1000
#define UTurnTime 2 * normalTurnTime
#define endCleaningTurnTime 100

RGBv colors;
int histlen = 5;
int colhist[5] = {-1, -1, -1, -1, -1};
float distancehis[5] = {5.0, 5.0,5.0,5.0,5.0};
float distance = 5;

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
  setMotors(-SteerSpeed, SteerSpeed); // might use tuning on the best speed
}

void turnRight()
{
  setMotors(SteerSpeed, -SteerSpeed);
}

void stopMotors()
{
  setMotors(0, 0);
}

unsigned long turnStartTime = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("im connected");
  ultrasonicSetup();
  motorSetup();
  colorSensorSetup();
  release(90); // Open claw to reduce footprint
  

}

void updateDistance(){
  float liveDistance = getDistanceCM();
  for(int i = 0; i < 4; i++){
    distancehis[i] = distancehis[i + 1];
  }
  distancehis[4] = liveDistance;
  float sum = 0.0;
  for (int i = 0; i < 5; i++) {
    sum += distancehis[i];
  }
  distance = sum / 5;
}

void loop()
{
  getRGB(&colors);
  int col = getMaximum(colors.redPW, colors.bluePW, colors.greenPW);
  addnew(colhist, col, histlen);                // Add new colour measurement to colour history

  updateDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance < distanceThreshold)
  {                                           // close to a wall, take the instruction
    float feedbackDistance = distance; // declared and intialize the latest distance var
    turnStartTime = millis();                 // restart the timer
    setMotors(0, 0);
    delay(50); // stop for a second to read the color properly
    int curr_color = colouraverage(colhist, histlen); // Get the average colour of the last 5 measurements
    Serial.println("you are close to wall");
    // Serial.print("Red PW = ");
    // Serial.print(colors.redPW);
    // Serial.print(" - Green PW = ");
    // Serial.print(colors.greenPW);
    // Serial.print(" - Blue PW = ");
    // Serial.println(colors.bluePW);
    float cpDistance = distance;
    Serial.print("Color: ");
    Serial.println(curr_color);
    if (curr_color == 1)
    {
      // Turn left if blue
      while ((feedbackDistance <= (cpDistance * 1.5 + 4)) || ((millis() - turnStartTime) <= normalTurnTime))
      {
        updateDistance();
        feedbackDistance = getDistanceCM();
        turnLeft();
      }
      unsigned int temp = millis();
      while ((millis() - temp) <= endCleaningTurnTime)
      {
        updateDistance();
        turnLeft();
      }
    }
    else if (curr_color == 2)
    {
      // Turn right if green
      while ((feedbackDistance <= (cpDistance * 1.5 + 4)) || ((millis() - turnStartTime) <= normalTurnTime))
      {
        updateDistance();
        feedbackDistance = getDistanceCM();
        turnRight();
      }
      unsigned int temp = millis();
      while ((millis() - temp) <= endCleaningTurnTime)
      {
        updateDistance();
        turnRight();
      }
    }
    else if (curr_color == 0)
    {
      // U-turn if red
      while ((millis() - turnStartTime) <= UTurnTime)
      {
        updateDistance();
        feedbackDistance = getDistanceCM();
        turnRight();
      }
      unsigned int temp = millis();
      while (millis() - temp <= endCleaningTurnTime)
      {
        updateDistance();
        turnRight();
      }
    }
    else if (curr_color == -1)
    {
      // go straight if black
      while ((millis() - turnStartTime) <= 3000)
      {
        updateDistance();
        turnRight();
      }
    }
    else
    {
      // default; empty case
    }
    stopMotors();
    delay(50);
  }
  else
  {
    moveForward();
  }
}
