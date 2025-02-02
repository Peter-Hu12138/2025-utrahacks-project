#include <Servo.h>

// Motor
#define IN1 A2
#define IN2 A3
#define IN3 A4
#define IN4 A5
#define EN_A 11
#define EN_B 10

Servo myServo;
int servoDelay = 1000;
// Motor pins, as variables (deprecrated)
// int EN_A = 11; //Enable pin for first motor
// int IN1 = A2; //control pin for first motor
// int IN2 = A3; //control pin for first motor
// int IN3 = A4; //control pin for second motor
// int IN4 = A5; //control pin for second motor
// int EN_B = 10; //Enable pin for second motor


void motorSetup() {
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN_B, OUTPUT);

  // set Servo pin
  myServo.attach(A1);
}

// Drive motors
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

void setMotors(int leftSpeed, int rightSpeed) {
    const char* leftDir = (leftSpeed >= 0) ? "FWD" : "REV";
    const char* rightDir = (rightSpeed >= 0) ? "FWD" : "REV";
    move_one(abs(leftSpeed), leftDir, IN1, IN2, EN_A);
    move_one(abs(rightSpeed), rightDir, IN3, IN4, EN_B);
}

void stop() {
    move_one(0, "FWD", IN1, IN2, EN_A);
    move_one(0, "REV", IN3, IN4, EN_B);
}

//Servo Motor
void grab(){
  myServo.write(90);
  Serial.println("grab");
  delay(servoDelay);
}

void release(int degree){
  myServo.write(90-degree);
  Serial.println("release");
  delay(servoDelay);
}
