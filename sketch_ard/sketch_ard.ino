#include <Servo.h>

Servo myServo;
int angle = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 5 * 60 * 1000UL; // 5 minutes in milliseconds

void setup() {
  myServo.attach(9);         // Servo signal pin connected to D9
  myServo.write(0);          // Start at 0 degrees

  pinMode(13, OUTPUT);       // Set pin 13 as output for LED
  digitalWrite(13, HIGH);    // Keep LED ON
}

void loop() {
  unsigned long currentMillis = millis();

  // Rotate servo every 5 minutes
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    angle += 60;
    if (angle > 180) {
      angle = 0;  // Reset to 0 after full sweep
    }

    myServo.write(angle);
  }
}