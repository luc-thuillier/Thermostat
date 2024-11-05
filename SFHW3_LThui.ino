// Luc Thuillier, SFHW3, thuillier.l@northeastern.edu

#include <LiquidCrystal.h>

// Initialize the library with the numbers of the LCD pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int tempSensorPin = A0;  // Temperature sensor on pin A0
const int potPin = A1;         // Potentiometer on pin A1 
const int blueLEDPin = 4;      // Blue LED on pin 4
const int redLEDPin = 7;       // Red LED on pin 7

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Welcome message
  lcd.print("Welcome!");
  delay(2000); // Display welcome message for 2 seconds

  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(tempSensorPin, INPUT);
}

void loop() {
  int setTemp = map(analogRead(potPin), 0, 1023, 60, 85); // Map potentiometer range to temperature range (60°F to 85°F)
  int temp = readTemperature(); // Read the current temperature

  lcd.clear();
  if (temp < setTemp - 1) {
    // If below range, Heater ON
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(blueLEDPin, LOW);
    lcd.print("Heater ON!");
  } else if (temp > setTemp + 1) {
    // If above range, AC ON
    digitalWrite(blueLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
    lcd.print("AC ON!");
  } else {
    // If Within range, LEDs OFF
    digitalWrite(blueLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print((char)223); // Degree symbol
    lcd.print("F");
  }
  // Display set temperature on the second line
  lcd.setCursor(0, 1);
  lcd.print("Set: ");
  lcd.print(setTemp);
  lcd.print((char)223); // Degree symbol
  lcd.print("F");

  delay(1000); // Refresh every second
}

int readTemperature() {
  int reading = analogRead(tempSensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ; // Convert to temperature 
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; // Convert to Fahrenheit
  return (int)temperatureF;
}