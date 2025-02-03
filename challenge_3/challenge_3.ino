#include "api.h"

// Sliding window variables for col sensor
RGBv colors;
int histlen = 5;
int colhist[5] = {-1, -1, -1, -1, -1};

void setup()
{
  // Variables for Color Pulse Width Measurements
  int redPW = 0;
  int greenPW = 0;
  int bluePW = 0;

  // Variable for tracking what it detected before
  int redEnable = 1;   // Flag for red detection. Once it's zero, red will never be detected again. 1 by default.
  int greenEnable = 0; // Flag for green detection. When it's 0, green will not be detected. Reverts to 1 when blue is detected. 0 by default.
  int blueEnable = 0;  // Flag for blue detection. When it's 0, blue will not be detected. Reverts to 1 when green is detected. 0 by default.
  int state = 0;       // State variable to keep track of the robot's position. 0 by default.

  pinMode(LED_BUILTIN, OUTPUT); // Initialize LED_BUILTIN pin as an output

  // Echo pins
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Echo pins end

  // Color sensor pins
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
  // Color sensor pins end
}

void blinkLED()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);                     // wait for a second
}

void loop()
{
  getRGB(&colors);
  int col = getMaximum(colors.redPW, colors.bluePW, colors.greenPW);
  addnew(colhist, col, histlen);                // Add new colour measurement to colour history
  int colavg = colouraverage(colhist, histlen); // Get the average colour of the last 5 measurements
  // Print output to Serial Monitor
  Serial.print("Red PW = ");
  Serial.print(colavg.redPW);
  Serial.print(" - Green PW = ");
  Serial.print(colavg.greenPW);
  Serial.print(" - Blue PW = ");
  Serial.println(colavg.bluePW);

  // Color detection end

  // Distance detection
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
  // Distance detection end

  // Sequence is R-G-B-G-B
  // The last two colors cannot be the same block detected as before.
  // Blink the LED when a color is detected.

  // Expected route:
  //  0. Go straight. R-B-R-G. First red is detected, ignore everything until green is detected.
  //  1. Turn right. (G)-G-R-B. Ignore everything until detecting blue.
  //  2. U-turn. (B)-R-G.
  //  3. Turn left. Keep running until wall is detected.
  //  4. Turn left again. Ignore everything until blue is detected. End.

  // State 0: Straight, detect red, keep running until green.
  if state
    == 0;
  {
    // Check if Red is detected
    if (redPW > greenPW && redPW > bluePW)
    {
      Serial.println("Red Detected");
      blinkLED();
      redEnable = 0;   // Red will never be detected again.
      greenEnable = 1; // Green can now be detected.
    }
  }

  // Check if Green is detected.
  else if state == 1;
  {
    if (greenPW > redPW && greenPW > bluePW)
    {
      Serial.println("Green Detected");
      blinkLED();
      greenEnable = 0; // Green can no longer be detected.
      blueEnable = 1;  // Blue can now be detected.
      // TODO: Turn right
    }
  }

  // Check if Blue is detected.
  else if state == 2;
  {
    if (bluePW > redPW && bluePW > greenPW)
    {
      Serial.println("Blue Detected");
      blinkLED();
      greenEnable = 1; // Green can now be detected.
      blueEnable = 0;  // Blue can no longer be detected.
      // TODO: U-turn
    }
  }

  // Check if Green is detected.
  else if state == 3;
  {
    if (greenPW > redPW && greenPW > bluePW)
    {
      Serial.println("Green Detected");
      blinkLED();
      greenEnable = 0; // Green can no longer be detected.
      blueEnable = 1;  // Blue can now be detected.
      // TODO: Turn left
    }
  }

  // Check if wall is detected.
  else if state == 4;
  {
    // TODO: Turn left once detecting wall
    // Don't change state until blue is detected.
  }

  // Check if Blue is detected.
  else if state == 4;
  {
    if (bluePW > redPW && bluePW > greenPW)
    {
      Serial.println("Blue Detected");
      blinkLED();
      greenEnable = 1; // Green can now be detected.
      blueEnable = 0;  // Blue can no longer be detected.
      // TODO: U-turn
    }
  }
}
