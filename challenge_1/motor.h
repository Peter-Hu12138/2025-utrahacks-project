#include <Servo.h>

Servo myServo;
// put your setup code here, to run once:
//Motor Pins
int EN_A = 11; //Enable pin for first motor
int IN1 = A2; //control pin for first motor
int IN2 = A3; //control pin for first motor
int IN3 = A4; //control pin for second motor
int IN4 = A5; //control pin for second motor
int EN_B = 10; //Enable pin for second motor
//Initializing variables to store data
int motor_speed;
int motor_speed1;
int x_pos;
int y_pos;
int servoDelay = 1000;

// Ultrasoun 12, 13
// Color Sensor 4-8

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
