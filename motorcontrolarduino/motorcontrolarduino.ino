#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <NewPing.h>

ESP8266WebServer server(80);

int D1 = 5;
int D2 = 4;
int D3 = 0;
int D4 = 2;

// Ultrasonic sensor pins
const int frontTriggerPin = 4;  // GPIO4
const int frontEchoPin = 5;     // GPIO5
const int backTriggerPin = 3;   // GPIO3
const int backEchoPin = 1;      // GPIO1

NewPing frontSonar(frontTriggerPin, frontEchoPin);
NewPing backSonar(backTriggerPin, backEchoPin);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() {
  // Read distances from all four sensors
  unsigned int frontDistance = frontSonar.ping_cm();
  unsigned int backDistance = backSonar.ping_cm();

  // Print the distances to the serial monitor
  Serial.println("Front Distance: " + String(frontDistance) + " cm");
  Serial.println("Back Distance: " + String(backDistance) + " cm");

  // Check if both front and back distances are <= 30 cm
  if (frontDistance <= 30 && backDistance <= 30) {
    // Turn left (adjust your motor control logic here)
    digitalWrite(D1, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D4, LOW);
    delay(500); // Adjust the delay as needed for your turning action
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    delay(1000); // Delay after turning
  }
  // Check if both front and back distances are > 30 cm
  else if (frontDistance > 30 && backDistance > 30) {
    // Move forward (adjust your motor control logic here)
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D4, LOW);
  } else {
    // Stop moving forward and turning (adjust your motor control logic here)
    digitalWrite(D1, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D4, LOW);
  }

  // Your additional motor control logic based on the distance readings
  // ...

  delay(100); // Adjust the delay as needed for your application
}
