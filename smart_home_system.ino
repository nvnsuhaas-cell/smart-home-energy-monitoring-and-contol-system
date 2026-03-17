#include <ESP8266WiFi.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);

// Relay pin
int relayPin = D1;

// ACS712 pin
int sensorPin = A0;

// Variables
float current = 0;
float power = 0;

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {

  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (3.3 / 1023.0);
  current = (voltage - 2.5) / 0.185;
  power = 230 * current;

  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/relayON") != -1) {
    digitalWrite(relayPin, LOW);
  }

  if (request.indexOf("/relayOFF") != -1) {
    digitalWrite(relayPin, HIGH);
  }

  if (request.indexOf("/data") != -1) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("");
    client.print("{\"current\":");
    client.print(current);
    client.print(",\"power\":");
    client.print(power);
    client.print("}");
    return;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.println("<h1>ESP8266 Smart System</h1>");
  client.println("<a href=\"/relayON\">ON</a><br>");
  client.println("<a href=\"/relayOFF\">OFF</a>");
}
