#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(2, OUTPUT);  // Left motor 1
  pinMode(3, OUTPUT);  // Right motor 1
  pinMode(4, OUTPUT);  // Left motor 2
  pinMode(5, OUTPUT);  // Right motor 2
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    Serial.println(command);  // Print the received command
    mySerial.write(command);  // Send the command to the Bluetooth module
  }

  if (mySerial.available()) {
    char command = mySerial.read();
    Serial.println("Received command from Bluetooth: " + String(command));  // Print the received command
    switch (command) {
      case 'F':  // Move forward
        Serial.println("Moving forward");
        digitalWrite(2, HIGH);  // Left motor 1 forward
        digitalWrite(3, LOW);  // Right motor 1 forward
        digitalWrite(4, LOW);  // Left motor 2 forward
        digitalWrite(5, HIGH);  // Right motor 2 forward
        break;
      case 'L':  // Turn left
        Serial.println("Turning left");
        digitalWrite(2, HIGH);   // Left motor 1 backward
        digitalWrite(3, LOW);  // Right motor 1 forward
        digitalWrite(4, LOW);  // Left motor 2 forward
        digitalWrite(5, LOW);  // Right motor 2 forward
        break;
      case 'R':  // Turn right
        Serial.println("Turning right");
        digitalWrite(2, LOW);  // Left motor 1 forward
        digitalWrite(3, LOW);  // Right motor 1 backward
        digitalWrite(4, LOW);  // Left motor 2 forward
        digitalWrite(5, HIGH);  // Right motor 2 forward
        break;
      case 'B':  // Move backward
        Serial.println("Moving backward");
        digitalWrite(2, LOW);  // Left motor 1 forward
        digitalWrite(3, HIGH);  // Right motor 1 forward
        digitalWrite(4, HIGH);   // Left motor 2 backward
        digitalWrite(5, LOW);   // Right motor 2 backward
        break;
      default:  // Stop
        Serial.println("Stopping");
        digitalWrite(2, LOW);   // Left motor 1 stopped
        digitalWrite(3, LOW);   // Right motor 1 stopped
        digitalWrite(4, LOW);   // Left motor 2 stopped
        digitalWrite(5, LOW);   // Right motor 2 stopped
        break;
    }
  }
}
