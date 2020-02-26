#include <Arduino.h>
#include "src/LeaphyEspOta.h"

LeaphyEspOta Leaphy("robot001");

int ledState = LOW;
const long blinkWaitInterval = 500;

void setup() {
  Leaphy.setupOta();
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  Leaphy.handleLoop();

  digitalWrite(LED_BUILTIN, LOW);
  delay(blinkWaitInterval);                   
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkWaitInterval);   
}
