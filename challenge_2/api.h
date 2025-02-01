#define trigPin 13
#define echoPin 12

float getColor()
{
    return 0.0; // TODO should be changed
}

void setMotors(int leftMotorSpeed, int rightMotorSpeed)
{
    // TODO
}

float getDistanceCM() // CM
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = (duration / 2) / 29.1; // Convert to centimeters
    return distance;
}

void adjustServo()
{
    // TODO
}

float getServoAngle()
{
    return 0.0; // TODO
}