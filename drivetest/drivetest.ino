#include "api.h"


void setup() {
  motorSetup();
  colorSensorSetup();
  ultrasonicSetup();
}

void loop() {
    // Example: Move forward with left motor at full speed, right motor at half speed (differential drive)
    setMotors(255, 128);
    delay(2000);

    // Example: Turn in place (left motor forward, right motor reverse)
    setMotors(255, -255);
    delay(2000);

    // Stop
    stop();
    delay(1000);


    // ultrasonic testing:
    Serial.print("Distance:");
    Serial.println(getDistanceCM());

    // color detection:
    RGBv rgbValue;
    getRGB(&rgbValue);
    Serial.print("Red PW = ");
	Serial.print(rgbValue.redPW);
	Serial.print(" - Green PW = ");
	Serial.print(rgbValue.greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(rgbValue.bluePW);

}
