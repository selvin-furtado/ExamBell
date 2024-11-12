#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
// 8 - buzzer
RTC_DS3231 rtc; // Create an RTC object
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address (0x27) if necessary
const int ledPin = 14; // LED connected to pin 13 (can change to your preferred pin)

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  digitalWrite(ledPin, LOW); // Turn off the LED initially
  Serial.begin(9600);

  turnOnLED(5);

  lcd.begin(16, 2); // Initialize the LCD
  lcd.backlight();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the RTC to the time this sketch was compiled
  }
}

void loop() {
  DateTime now = rtc.now();
  displayTime(now);

  // Check and control the LED based on the schedule
  controlLED(now);

  delay(1000); // Update every second
}

// Function to display time on the LCD
void displayTime(DateTime now) {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  if (now.hour() < 10) lcd.print("0"); // Add leading zero
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0"); // Add leading zero
  lcd.print(now.minute());
}

// Function to control LED based on the time schedule
void controlLED(DateTime now) {
  int hour = now.hour();
  int minute = now.minute();

  // Define the time conditions for LED on/off
  if ((hour == 10 && minute == 20) || (hour == 11 && minute == 30) || 
      (hour == 12 && minute == 30) || (hour == 13 && minute == 20) || 
      (hour == 14 && minute == 20) || (hour == 15 && minute == 30) || 
      (hour == 16 && minute == 30) || (hour == 17 && minute == 20)) {
    turnOnLED(7); // Turn on LED for 7 seconds
  } 
  else if ((hour == 10 && minute == 30) || (hour == 13 && minute == 30) || 
           (hour == 14 && minute == 30) || (hour == 17 && minute == 30)) {
    turnOnLED(15); // Turn on LED for 15 seconds
  }
}

// Function to turn on the LED for a specified duration
void turnOnLED(int duration) {
  digitalWrite(ledPin, HIGH); // Turn on the LED
  delay(duration * 1000); // Keep LED on for the specified duration (in milliseconds)
  digitalWrite(ledPin, LOW); // Turn off the LED
}
