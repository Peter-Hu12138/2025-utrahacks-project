// Define color sensor pins
#define OE_PIN 3
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

typedef struct {
	int redPW;
  	int bluePW;
  	int greenPW;
} RGBv;

void colorSensorSetup(){
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

int getRedPW() {
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);

	return pulseIn(sensorOut, LOW);
}

int getGreenPW() {
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	
	return pulseIn(sensorOut, LOW);
}

int getBluePW() {
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);

	return pulseIn(sensorOut, LOW);
}



// Structure for Color Pulse Width Measurements
void getRGB(RGBv *rgb) {

	rgb->redPW = getRedPW();
	delay(200);

	rgb->greenPW = getGreenPW();
	delay(200);

	rgb->bluePW = getBluePW();

  delay(200);
}

int getDelta(RGBv *rgb,int origRed,int origBlue, int origGreen) {
  return (abs(rgb->redPW - origRed) + abs(rgb->bluePW - origBlue) + abs(rgb->greenPW - origGreen));
}

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