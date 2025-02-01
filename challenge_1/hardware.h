#include <Servo.h>

Servo myServo;
// put your setup code here, to run once:
//Motor Pins
int EN_A = 11; //Enable pin for first motor
int IN1 = 9; //control pin for first motor
int IN2 = A2; //control pin for first motor
int IN3 = A3; //control pin for second motor
int IN4 = 6; //control pin for second motor
int EN_B = 10; //Enable pin for second motor
//Initializing variables to store data
int motor_speed;
int motor_speed1;
int x_pos;
int y_pos;
int servoDelay = 1000;


void loop() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, 90);
  Serial.println("Wheel A");

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, 90);
  Serial.println("Wheel B");

  //servo
  release(90);
  grab();

  // // put your main code here, to run repeatedly:
  // x_pos = 700 ; //Reading the horizontal movement value
  // y_pos = 600 ; //Reading the vertical movement value

  // if (x_pos < 400){ //Rotating the left motor in clockwise direction
  // motor_speed = map(x_pos, 400, 0, 0, 255); //Mapping the values to 0-255 to move the motor
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, HIGH);
  // analogWrite(EN_A, motor_speed);
  // }

  // else if (x_pos>400 && x_pos <600){ //Motors will not move when the joystick will be at center
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, LOW);
  // }

  // else if (x_pos > 600){ //Rotating the left motor in anticlockwise direction
  // motor_speed = map(x_pos, 600, 1023, 0, 255);
  // digitalWrite(IN1, HIGH);
  // digitalWrite(IN2, LOW);
  // analogWrite(EN_A, motor_speed);
  // }

  // if (y_pos < 400){ //Rotating the right motor in clockwise direction
  // motor_speed1 = map(y_pos, 400, 0, 0, 255);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, HIGH);
  // analogWrite(EN_B, motor_speed1);
  // }

  // else if (y_pos>400 && y_pos <600){
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, LOW);
  // }

  // else if (y_pos > 600){ //Rotating the right motor in anticlockwise direction
  // motor_speed1 = map(y_pos, 600, 1023, 0, 255);
  // digitalWrite(IN3, HIGH);
  // digitalWrite(IN4, LOW);
  // analogWrite(EN_B, motor_speed1);
  // }

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

