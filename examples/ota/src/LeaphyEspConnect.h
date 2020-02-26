/*
	Library containing functionality for connecting Leaphy robot to WiFi
*/
#ifndef LeaphyEspConnect_h
#define LeaphyEspConnect_h

#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

class LeaphyEspConnect {
	public:
		LeaphyEspConnect(String robotId);
		void setupConnect();
		void handleLoop();
};

#endif