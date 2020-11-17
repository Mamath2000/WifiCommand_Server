/* Create a WiFi access point and provide a web server on it. */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESPap";
const char *password = "";

ESP8266WebServer server(80);

void handleSentVar() {
  if (server.hasArg("x1") && server.hasArg("y1") && 
      server.hasArg("x2") && server.hasArg("y2")) { // this is the variable sent from the client
    server.send(200, "text/html", "Data received");
    int readingIntX = server.arg("x1").toInt();
    int readingIntY = server.arg("y1").toInt();
    Serial.print("J1:");Serial.print(readingIntX);
    Serial.print(" - ");Serial.println(readingIntY);
    readingIntX = server.arg("x2").toInt();
    readingIntY = server.arg("y2").toInt();
    Serial.print("J2:");Serial.print(readingIntX);
    Serial.print(" - ");Serial.println(readingIntY);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
