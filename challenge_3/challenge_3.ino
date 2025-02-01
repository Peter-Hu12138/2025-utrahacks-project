#include "api.h"
// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

void setup()
{
  // Variables for Color Pulse Width Measurements
  int redPW = 0;
  int greenPW = 0;
  int bluePW = 0;
  pinMode(LED_BUILTIN, OUTPUT);  //Initialize LED_BUILTIN pin as an output

  //Echo pins
      Serial.begin(9600);
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
 //Echo pins end

  //Color sensor pins
      //Set S0 - S3 as outputs
      pinMode(S0, OUTPUT);
      pinMode(S1, OUTPUT);
      pinMode(S2, OUTPUT);
      pinMode(S3, OUTPUT);

      // Set Pulse Width scaling to 20%
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);

      // Set Sensor output as input
      pinMode(sensorOut, INPUT);

      // Setup Serial Monitor
      Serial.begin(9600);
  //Color sensor pins end
}

void blinkLED()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

long detectDistance()
{
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

void loop()
{
  //Sequence is R-G-B-G-B
  //The last two colors cannot be the same block detected as before.
  //Blink the LED when a color is detected.

  //Expected route:
  // 1. Go straight. R-B-R-G. First red is detected, ignore everything until green is detected.
  // 2. Turn right. (G)-G-R-B. Ignore everything until detecting blue.
  // 3. U-turn. (B)-R-G.
  // 4. Turn left. Keep running until wall is detected.
  // 5. Turn left again. Ignore everything until blue is detected. End.  



  //Color detection
    // Read Red Pulse Width
    redPW = getRedPW();
    // Delay to stabilize sensor
    delay(200);

    // Read Green Pulse Width
    greenPW = getGreenPW();
    // Delay to stabilize sensor
    delay(200);

    // Read Blue Pulse Width
    bluePW = getBluePW();
    // Delay to stabilize sensor
    delay(200);

    // Print output to Serial Monitor
    Serial.print("Red PW = ");
    Serial.print(redPW);
    Serial.print(" - Green PW = ");
    Serial.print(greenPW);
    Serial.print(" - Blue PW = ");
    Serial.println(bluePW);
	//Color detection end

  //If statement to check the color
      // Check if Red is detected
      if (redPW > greenPW && redPW > bluePW)
      {
        Serial.println("Red Detected");
        // Blink LED
        // TODO
      }
      // Check if Green is detected
      else if (greenPW > redPW && greenPW > bluePW)
      {
        Serial.println("Green Detected");
        // Blink LED
        // TODO
      }
      // Check if Blue is detected
      else if (bluePW > redPW && bluePW > greenPW)
      {
        Serial.println("Blue Detected");
        // Blink LED
        // TODO
      }
      // No color detected
      else
      {
        Serial.println("No Color Detected");
      } 
    //Color if statements end




}
