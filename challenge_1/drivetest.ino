#include "api.h"


void setup() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(EN_A, OUTPUT);
    pinMode(EN_B, OUTPUT);
}

void loop() {
    // Example: Move forward with left motor at full speed, right motor at half speed (differential drive)
    setMotors(255, 128);
    delay(2000);

    // Example: Turn in place (left motor forward, right motor reverse)
    setMotors(255, -255);
    delay(2000);

    // Stop
    setMotors();
    delay(1000);
}
