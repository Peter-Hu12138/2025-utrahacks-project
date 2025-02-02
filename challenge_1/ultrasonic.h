#define trigPin 13
#define echoPin 12

void ultrasonicSetup() {
    pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
