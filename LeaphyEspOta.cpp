#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <ArduinoWebsockets.h>
#include <jsonlib.h>

#include "LeaphyEspOta.h"

using namespace websockets;

/*
Leaphy robot is switched on
It can't connect to internet
It shows SSID of Wifi network (random Leaphy-XXXX)
Peoples connect it to WiFi
It registers itself to api using MAC address
It receives and shows a pairing code
Peoples pair their client using this code
Client is linked to robot using MAC address

People upload new sketch to API
Robot gets location from API and updates itself
After update, it can connect to WiFi
It registers itself as being back
It gets the same pairing code

the client disconnects (but remembers the last pairing code)
if the pairing code is still valid, it will pair automatically
if the pairing code has changed, then pairing will have to happen again

*/

// The url probably be injected just before compilation time
const char* websockets_server = "wss://ccsb7byy76.execute-api.eu-west-1.amazonaws.com/test/";
WebsocketsClient client;

voi setupWifi(){
  randomSeed(analogRead(0)); // Gets a random seed from analog pin noise
  long randomNr = random(9999);
  WiFiManager wifiManager;
  String ssid = "Leaphy-" + randomNr;
  // TODO: Show ssid in screen
  wifiManager.autoConnect(ssid);
}

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    const messageData = message.data();
    Serial.println(messageData);
    const event = jsonExtract(messageData, "event");

    // If pairing code, save and show it on the screen
    if(event == "PAIRINGCODE_UPDATED"){
        Serial.print("Pairing Code Updated Message Received: ");
        const pairingCode = jsonExtract(messageData, "message");
        Serial.println(pairingCode);
    }
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

void setupWS(){
    
    // Setup Callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    
    // Connect to server
    client.connect(websockets_server);

    // Register the robot with its mac address
    string registerMessage = 
        "{ \"action\": \"register-robot\", \"robotId\": \"" + WiFi.macAddress() + "\"}"
    client.send(registerMessage);
}

void LeaphyEspOta::setupOta(){
    Serial.begin(115200);
    Serial.println("Starting OTA Setup");
    setupWifi();
    Serial.println("Connected to WiFi, connecting to WS API");
    setupWS();
}

void LeaphyEspOta::handleLoop(){
	// Handle the WS stuff
  client.poll();
}





