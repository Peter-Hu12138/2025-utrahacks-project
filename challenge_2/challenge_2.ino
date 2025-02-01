#include "api.h"

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{

  //Black - Go straight
  //Blue - Turn left
  //Green - Turn right
  //Red - U-turn

  //High level idea:
  // 1. Read the distance from the ultrasonic sensor
  // 2. Make an if statement to check if the distance is less than 5cm.
  // 3. If the distance is less than 5cm, check the color beneath the robot. Branch based on the color.

  long distance = getDistanceCM();

  if (distance >= 200 || distance <= 0)
  {
    Serial.println("Out of range");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
