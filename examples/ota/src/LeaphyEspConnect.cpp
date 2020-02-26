#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "LeaphyEspConnect.h"

String RobotId;

LeaphyEspConnect::LeaphyEspConnect(String robotId)
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Setting up connect for robot " + robotId);
	RobotId = robotId;
}

ESP8266WebServer server(80);

void setupWifiStationMode(){
  WiFi.begin(); // Uses the WiFi credentials last entered
}

// Handles requests to the robot's web page root
void handleRoot() {
  String s = "<HTML><HEAD><TITLE>Leaphy Robot " + RobotId + "</TITLE></HEAD>"
+ "<BODY>"
+	"<form method='post' enctype='application/x-www-form-urlencoded' action='postform/'>"
+ "       <input type='text' name='SSID' >"
+ "       <input type='text' name='Key' >"
+ "       <input type='submit' value='Submit'>"
+ "    </form>"	
+ "</BODY>"
+ "</HTML>";
  server.send(200, "text/html", s);
}

void handleForm() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    Serial.println("Connecting to wifi");
    WiFi.begin(server.arg(0).c_str(), server.arg(1).c_str());

    String message = "Connected!";
    server.send(200, "text/plain", message);
  }
}

void handleWiFiStatusRequest() {
    String message = "Connected!";
    server.send(200, "text/plain", message);
}

void setupWifiAccessPointMode(){
  WiFi.softAP(RobotId);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/postform/", handleForm);
  server.begin();
}

void LeaphyEspConnect::setupConnect(){
  WiFi.mode(WIFI_AP_STA);
	setupWifiStationMode();
	setupWifiAccessPointMode();
}

void LeaphyEspConnect::handleLoop(){
	server.handleClient();
  Serial.println(WiFi.localIP());
  delay(1000);
}




