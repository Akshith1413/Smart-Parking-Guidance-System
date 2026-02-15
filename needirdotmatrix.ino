#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD at I2C address 0x27 (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// LED pins for ultrasonic
const int ledNear = 8;    // very near
const int ledMedium = 12; // medium
const int ledFar = 13;    // far

// Buzzer pin
const int buzzerPin = 7;

// IR sensors and respective LEDs
const int irPins[4] = {2, 3, 4, 5};   // IR sensor input pins
const int irLeds[4] = {A0, A1, A2, A3}; // LEDs for each IR sensor

long duration;
int distance;

void setup() {
  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Ultrasonic LEDs
  pinMode(ledNear, OUTPUT);
  pinMode(ledMedium, OUTPUT);
  pinMode(ledFar, OUTPUT);

  // Buzzer
  pinMode(buzzerPin, OUTPUT);

  // IR sensor pins and LEDs
  for (int i = 0; i < 4; i++) {
    pinMode(irPins[i], INPUT);
    pinMode(irLeds[i], OUTPUT);
  }

  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ultrasonic + IR");
  delay(1500);
  lcd.clear();
}

void loop() {
  // --------- Ultrasonic Sensor Part ----------
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10us HIGH pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance (cm)
  distance = duration * 0.034 / 2;

  Serial.print("US Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Reset LEDs & buzzer
  digitalWrite(ledNear, LOW);
  digitalWrite(ledMedium, LOW);
  digitalWrite(ledFar, LOW);
  noTone(buzzerPin);

  // Show distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print(" cm");

  // Decide which LED/buzzer to turn on
  if (distance <= 10) {           // Very near
    digitalWrite(ledNear, HIGH);
    tone(buzzerPin, 1000);
    lcd.setCursor(0, 1);
    lcd.print("Status: VERY NEAR");
  } 
  else if (distance <= 20) {      // Medium
    digitalWrite(ledMedium, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status: MEDIUM   ");
  } 
  else if (distance <= 35) {      // Far
    digitalWrite(ledFar, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status: FAR      ");
  } 
  else {                          // Beyond range
    lcd.setCursor(0, 1);
    lcd.print("Status: CLEAR    ");
  }

  // --------- IR Sensor Part ----------
  for (int i = 0; i < 4; i++) {
    int irState = digitalRead(irPins[i]);  // read IR sensor
    if (irState == LOW) {  
      // Assuming IR sensor gives LOW when obstacle detected
      digitalWrite(irLeds[i], HIGH);
      Serial.print("IR Sensor ");
      Serial.print(i + 1);
      Serial.println(": Obstacle");
    } else {
      digitalWrite(irLeds[i], LOW);
    }
  }

  delay(300); // refresh rate
}
