#include <Arduino.h>
#include <string.h>  // Required for strcmp()

// Convention: 1,3 LOW for forward; 2,4 LOW for backward
void move_one(int speed, const char* dir, int inPin1, int inPin2, int pwmPin) {
    if (strcmp(dir, "FWD") == 0) {  
        digitalWrite(inPin1, LOW);
        digitalWrite(inPin2, HIGH);
    } 
    else if (strcmp(dir, "REV") == 0) {  
        digitalWrite(inPin1, HIGH);
        digitalWrite(inPin2, LOW);
    }
    analogWrite(pwmPin, speed);
}

void drive(int leftSpeed, int rightSpeed) {
    const char* leftDir = (leftSpeed >= 0) ? "FWD" : "REV";
    const char* rightDir = (rightSpeed >= 0) ? "FWD" : "REV";
    move_one(abs(leftSpeed), leftDir, IN1, IN2, EN_A);
    move_one(abs(rightSpeed), rightDir, IN3, IN4, EN_B);
}

void stop() {
    move_one(0, "FWD", IN1, IN2, EN_A);
    move_one(0, "REV", IN3, IN4, EN_B);
}
