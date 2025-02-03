// Define color sensor pins
#define OE_PIN 3
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

typedef struct
{
  int redPW;
  int bluePW;
  int greenPW;
} RGBv;

void colorSensorSetup()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(OE_PIN, OUTPUT);

  digitalWrite(OE_PIN, LOW);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

int getRedPW()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  return pulseIn(sensorOut, LOW);
}

int getGreenPW()
{
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  return pulseIn(sensorOut, LOW);
}

int getBluePW()
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  return pulseIn(sensorOut, LOW);
}

// Structure for Color Pulse Width Measurements
void getRGB(RGBv *rgb)
{

  // Convert frequency to RGB values (mapping range may need calibration)
  delay(25);
  rgb->redPW = map(getRedPW(), 100, 500, 255, 0);
  delay(25);
  rgb->greenPW = map(getGreenPW(), 200, 600, 255, 0);
  delay(25);
  rgb->bluePW = map(getBluePW(), 100, 500, 255, 0);

  // Clamp values to ensure they are in the range 0-255
  rgb->redPW = constrain(rgb->redPW, 0, 255);
  rgb->greenPW = constrain(rgb->greenPW + 50, 0, 255);
  rgb->bluePW = constrain(rgb->bluePW, 0, 255);

  Serial.print("R: ");
  Serial.print(rgb->redPW);
  Serial.print(" G: ");
  Serial.print(rgb->greenPW);
  Serial.print(" B: ");
  Serial.println(rgb->bluePW);
}

int getDelta(RGBv *rgb, int origRed, int origBlue, int origGreen)
{
  return (abs(rgb->redPW - origRed) + abs(rgb->bluePW - origBlue) + abs(rgb->greenPW - origGreen));
}

int getMinimum(int red, int blue, int green)
{

  // get current state based on which color value is the lowest
  if (min(red, blue) == red && min(red, green) == red)
  {
    return 0;
  }
  else if (min(blue, red) == blue && min(blue, green) == blue)
  {
    return 1;
  }
  else
  {
    return 2;
  }
}

int getMaximum(int red, int blue, int green)
{
  // If all colours below certain threshold, assume black
  int blk_thres = 15;
  int wht_thres = 180;
  if (((red < blk_thres) && (green < blk_thres) && (blue < blk_thres)) | ((red > blk_thres) && (green > blk_thres) && (blue > blk_thres)))
  {
    return -1; //-1 represents black
  }

  // get current state based on which color value is the lowest
  if (max(red, blue) == red && max(red, green) == red)
  {
    return 0;
  }
  else if (max(blue, red) == blue && max(blue, green) == blue)
  {
    return 1;
  }
  else
  {
    return 2;
  }
}
