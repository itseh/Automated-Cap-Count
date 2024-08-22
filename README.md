Project Overview:
This project is designed to count the number of people entering and exiting a specific area based on weight measurements. It uses two load cells (through the HX711 modules) to detect changes in weight, which indicate whether a person has entered or exited the area. A motion sensor (PIR) is used to detect when someone is present. The count of people is displayed on an LCD.

Components and Communication Protocols:
1. Load Cells & HX711 Modules:

Function: The load cells measure weight. When someone steps on the load cell, the weight is measured, and the system determines if it exceeds a threshold (e.g., 60 units) to count the person as entering or exiting.
Communication Protocol: The HX711 module, which is an ADC (Analog-to-Digital Converter), converts the analog signals from the load cells into digital data. The communication between the HX711 modules and the Arduino uses a serial protocol with two pins: DOUT (Data Out) and SCK (Clock). The Arduino sends a clock signal via the SCK pin, and the HX711 sends back the digital weight data via the DOUT pin.

2. PIR Motion Sensor:

Function: Detects the presence of a person by sensing motion. When motion is detected, it triggers an event in the Arduino to update the LCD with the current count of people.
Communication Protocol: The PIR sensor uses a simple digital signal to communicate with the Arduino. When motion is detected, the sensor outputs a HIGH signal on its output pin, which the Arduino reads via digitalRead().

3. LCD Display:

Function: Displays the current count of people inside the monitored area.
Communication Protocol: The LCD is controlled by the Arduino using a parallel communication protocol via the specified pins (RS, EN, D4-D7). The Arduino sends control and data signals to the LCD to update the display.

4. Interrupts:
Function: An interrupt is attached to a specific pin (pin 0 in this case) to handle real-time events, such as someone entering or exiting the area. The interrupt triggers the checkWeight() function whenever the condition (HIGH signal) is met, ensuring the system responds immediately to changes in weight.
Communication Protocol: Interrupts don't use a communication protocol per se, but they are essential for handling real-time events in microcontroller applications.

Workflow
Setup:
- The system initializes the LCD, HX711 modules, and motion sensor.
- It calibrates and tares the load cells (zeroing them out).
  
Loop:
- Continuously checks the PIR sensor for motion. When motion is detected, the current count of people is displayed on the LCD.
Interrupt:
- The checkWeight() function is triggered by the interrupt to determine if someone has entered or exited based on the weight detected by the load cells. It increments or decrements the count accordingly and updates the LCD display.


Demo video - https://www.youtube.com/watch?v=UUJDbGnUpz8
