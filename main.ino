// Include required libraries
#include <LiquidCrystal.h>

// Define pins
const int irSensor = 2;
const int echoPin = 3;
const int trigPin = 4;
const int motorPin1 = 5;
const int motorPin2 = 6;
const int buzzerPin = 7;
const int ledPin = 8;

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(9, 10, 11, 12, A0, A1);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Pin Modes
  pinMode(irSensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Railway Safety");
  delay(2000);
  lcd.clear();
}

void loop() {
  // IR Sensor detection
  int trainDetected = digitalRead(irSensor);

  // Ultrasonic Sensor distance measurement
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (trainDetected == LOW && distance < 50) {
    // Train is approaching and present

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Train Incoming");
    lcd.setCursor(0, 1);
    lcd.print("Closing Gate");

    // Turn on buzzer and LED
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);

    // Close gate (rotate motor)
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(3000); // Time to close gate
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

  } else {
    // No train or far

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Train");
    lcd.setCursor(0, 1);
    lcd.print("Gate Open");

    // Turn off buzzer and LED
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    // Open gate (rotate motor in opposite direction)
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(3000); // Time to open gate
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }

  delay(1000); // Loop delay
}
