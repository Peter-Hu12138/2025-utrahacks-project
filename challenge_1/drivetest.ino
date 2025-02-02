#include "api.h"

RGBv rgbValue;
void setup() {
  colorSensorSetup();
  motorSetup();
  ultrasonicSetup();
  myServo.write(0);
  setMotors(100, 100);
}

void loop() {


    // ultrasonic testing:
    float distance = getDistanceCM();
    Serial.print("Distance:");
    Serial.println(distance);

    // color detection:
    grab();

    getRGB(&rgbValue);
     Serial.print("Red PW = ");
     Serial.print(rgbValue.redPW);
     Serial.print(" - Green PW = ");
     Serial.print(rgbValue.greenPW);
     Serial.print(" - Blue PW = ");
     Serial.println(rgbValue.bluePW);
    delay(500);
    release(60);
}
