#include <Stepper.h>  // Include the Stepper library

// Define the number of steps per revolution for your motor
const int stepsPerRevolution = 2038; // Change this to match your motor's specifications

// Initialize the Stepper library on the motor pins
Stepper motor1(stepsPerRevolution, 2, 3, 4, 5);
Stepper motor2(stepsPerRevolution, 6, 7, 8, 9);
Stepper motor3(stepsPerRevolution, 10, 11, 12, 13);
Stepper motor4(stepsPerRevolution, A0, A1, A2, A3);

// Define the password
const String password = "12345"; // Change this to your desired password

void setup() {
  Serial.begin(9600); // Start serial communication
  motor1.setSpeed(9); // Set speed for Motor 1
  motor2.setSpeed(9); // Set speed for Motor 2
  motor3.setSpeed(9); // Set speed for Motor 3
  motor4.setSpeed(9); // Set speed for Motor 4
  Serial.println("Enter The Passkey To Access The Motor :)");
}

void loop() {
  // Ask for the password
  String inputPassword = "";
  while (inputPassword != password) {
    if (Serial.available() > 0) {
      char key = Serial.read(); // Read a key from the Serial Monitor
      if (key == '\n' || key == '\r') { // Check for Enter key
        if (inputPassword == password) {
          Serial.println("Access granted.");
        } else {
          Serial.println("Access denied. Try again:");
        }
        inputPassword = ""; // Clear the input for the next attempt
      } else {
        inputPassword += key; // Append the key to the password string
        Serial.print(key); // Show the current input
      }
    }
  }

  // Now that access is granted, wait for motor commands
  Serial.println("Enter '1', '2', '3', or '4' to control the motors:");
  
  // Wait for motor command input
  while (true) {
    if (Serial.available() > 0) {
      char motorKey = Serial.read(); // Read the motor command
      switch (motorKey) {
        case '1':
          Serial.println("Rotating Motor 1");
          motor1.step(stepsPerRevolution);
          break;
        case '2':
          Serial.println("Rotating Motor 2");
          motor2.step(stepsPerRevolution);
          break;
        case '3':
          Serial.println("Rotating Motor 3");
          motor3.step(stepsPerRevolution);
          break;
        case '4':
          Serial.println("Rotating Motor 4");
          motor4.step(stepsPerRevolution);
          break;
        default:
          Serial.println("");
          break;
      }
      // Prompt for the next command
      Serial.println("To Control More Moters, You can enter the Product Number:)");
    }
  }
}