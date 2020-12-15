#include <ESP8266WiFi.h>
 
const char* ssid = "isdae";
const char* password = "2100105964";
 

WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(LED_BUILTIN, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=ON") != -1){
    digitalWrite(LED_BUILTIN, LOW);
    value = LOW;
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
//  client.println("<!DOCTYPE HTML>");
//  client.println("<html>");
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (3.2 / 1023.0);
  client.println(voltage);
//  client.print("<br>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
