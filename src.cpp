#include <Servo.h>   // Include the servo library

Servo servo;         // Create a Servo object
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;
int led = 10;
long duration, dist, average;
long aver[3];        // Array for average

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);  // Attach the servo to the servoPin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.write(0);         // Close cap on power on
  delay(100);
  servo.detach();         // Detach the servo (no need to control it immediately)
}

void measure() {
  digitalWrite(10, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;    // Obtain distance
}

void loop() {
  for (int i = 0; i <= 2; i++) {   // Average distance
    measure();
    aver[i] = dist;
    delay(10);              // Delay between measurements
  }
  dist = (aver[0] + aver[1] + aver[2]) / 3;

  if (dist < 50) {  // Change distance as per your need
    servo.attach(servoPin);  // Attach the servo when you want to use it
    delay(1);
    servo.write(0);
    delay(3000);
    servo.write(150);
    delay(1000);
    servo.detach();          // Detach the servo when you're done using it
  }

  Serial.print(dist);
}