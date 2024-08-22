#include <TimeLib.h>
#include <TimeAlarms.h>
#include <HX711.h>
#include <LiquidCrystal.h>

// Define pins for the HX711 scales
#define DOUT1 8
#define SCK1 9
#define DOUT2 11
#define SCK2 12  // Added the missing pin number for SCK2

// Define pins for the LCD
const int rs = 35, en = 37, d4 = 47, d5 = 49, d6 = 51, d7 = 53;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Initialize the LCD with the defined pins

// Initialize HX711 scales
HX711 scale1;
HX711 sl2;

// Calibration factor and counter
float cal1 = 450;  // Fixed the typo 'call' to 'cal1'
int count = 0;


// hardware Config

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  scale1.begin(DOUT1, SCK1);  // Initialize the first scale with the data and clock pins
  scale1.set_scale();  // Set the scale calibration factor (you may want to pass a value here)
  scale1.tare();  // Reset the scale to zero

  sl2.begin(DOUT2, SCK2);  // Initialize the second scale with the data and clock pins
  sl2.set_scale();  // Set the scale calibration factor (you may want to pass a value here)
  sl2.tare();  // Reset the second scale to zero

  pinMode(MOTION, INPUT);  // Set the motion sensor pin as an input
  pinMode(led, OUTPUT);  // Set the LED pin as an output

  attachInterrupt(digitalPinToInterrupt(0), checkWeight, HIGH);  // Attach an interrupt to pin 0 to trigger the checkWeight function on a HIGH signal
}


//Setup Function 

void loop() {
  int pirStat = digitalRead(MOTION);  // Reads the state of the PIR motion sensor

  if (pirStat == HIGH) {  // Checks if motion is detected
    lcd.print(count);     // Displays the value of 'count' on the LCD
    delay(4000);          // Waits for 4 seconds
    lcd.clear();          // Clears the LCD screen
  }
}

//Loop Function 

void checkWeight() {
  int enter = 0;
  int exitt = 0;

  // Set the scale for the first sensor
  scale1.set_scale(cal1);
  enter = scale1.get_units();  // Get the weight measurement from the first scale

  // Check if the weight exceeds 60 units (someone is entering)
  if (enter > 60) {
    count++;  // Increment the count
    lcd.clear();  // Clear the LCD screen
    lcd.print(count);  // Display the updated count on the LCD
    delay(1000);  // Wait for 1 second
  }

  // Set the scale for the second sensor
  sl2.set_scale(cal1);
  exitt = sl2.get_units();  // Get the weight measurement from the second scale

  // Check if the weight exceeds 60 units (someone is exiting)
  if (exitt > 60) {
    count--;  // Decrement the count
    lcd.clear();  // Clear the LCD screen
    lcd.print(count);  // Display the updated count on the LCD
    delay(1000);  // Wait for 1 second
  }
}

//Interrupt Function