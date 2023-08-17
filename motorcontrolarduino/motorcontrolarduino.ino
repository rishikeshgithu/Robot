#include <ESP8266WiFi.h>

const char* ssid = "srinivas";
const char* password = "rishi1234";

WiFiServer server(80);

int D1 = 5;
int D2 = 4;
int D3 = 0;
int D4 = 2;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print ESP8266 IP address
  Serial.println("IP address: " + WiFi.localIP().toString());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected");
    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    response += "<!DOCTYPE HTML>\r\n";
    response += "<html><body>";

    response += "<h1>ESP8266 Web Server</h1>";

    response += "<form method='post'>";
    response += "<button name='btn' value='D1'>Turn D1 ON</button>";
    response += "<button name='btn' value='D2'>Turn D2 ON</button>";
    response += "<button name='btn' value='D3'>Turn D3 ON</button>";
    response += "<button name='btn' value='D4'>Turn D4 ON</button><br>";
    response += "</form>";

    response += "</body></html>";

    client.println(response);
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
    
    if (client.available()) {
      String request = client.readStringUntil('\r');
      if (request.indexOf("D1") != -1) {
        digitalWrite(D1, HIGH);
        Serial.println("D1 is now ON");
        delay(1000); // Keep D1 on for 1 second
        digitalWrite(D1, LOW);
        Serial.println("D1 is now OFF");
      }
      if (request.indexOf("D2") != -1) {
        digitalWrite(D2, HIGH);
        Serial.println("D2 is now ON");
        delay(1000);
        digitalWrite(D2, LOW);
        Serial.println("D2 is now OFF");
      }
      if (request.indexOf("D3") != -1) {
        digitalWrite(D3, HIGH);
        Serial.println("D3 is now ON");
        delay(1000);
        digitalWrite(D3, LOW);
        Serial.println("D3 is now OFF");
      }
      if (request.indexOf("D4") != -1) {
        digitalWrite(D4, HIGH);
        Serial.println("D4 is now ON");
        delay(1000);
        digitalWrite(D4, LOW);
        Serial.println("D4 is now OFF");
      }
    }
  }
}
