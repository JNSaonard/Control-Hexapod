//#include <iostream>
#include <iomanip>
// Define Input Connections
#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 3
#define CH5 4
#define CH6 5

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;

// Boolean to represent switch value
bool ch6Value;

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}

void loop() {
  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, 0);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readSwitch(CH6, false);
  
  // Map values to the desired range
  float ch3Speed = ch3Value / 100.0 * 2.0; // Scale the value

  // Read the direction from CH1
  int ch1Value = readChannel(CH1, -100, 100, 0);
  String direction;
  if (ch1Value < -50) {
    direction = "kiri";
  } else if (ch1Value > 50) {
    direction = "kanan";
  } else {
    direction = "lurus";
  }

  if (ch2Value < -50) {
    direction += ", mundur";
  } else if (ch2Value > 50) {
    direction += ", maju";
  } else {
    direction += ", maju";
  }

  if (ch3Value == -100) {
  direction = "diam";// Set speed to 0
  }

  // Print to Serial Monitor
  Serial.print("Robot berjalan arah ");
  Serial.print(direction);
  Serial.print(" dengan kecepatan: ");
  Serial.print(ch3Speed, 2); // Print speed with 2 decimal places
  Serial.println(" m/s");
  
  delay(500);
}
