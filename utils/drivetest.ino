#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define EN_A 9
#define EN_B 10

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
    drive(255, "FWD", 128, "FWD");
    delay(2000);

    // Example: Turn in place (left motor forward, right motor reverse)
    drive(255, "FWD", 255, "REV");
    delay(2000);

    // Stop
    stop();
    delay(1000);
}
