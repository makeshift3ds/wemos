/*
 *  Connect to Wifi
 *  Setup OTA updates
 *  Connect to Mosquitto MQTT Server
 */
#include "Superhome.h"

const char *ssid = "****";
const char *password = "****";
const char *mqttServer = "****";

int relayPin = D4;
int ledPin = D1;
int rfPin = D3;

Superhome Superhome("office/controller");

void setup()
{
  Superhome.setupSerial(115200);
  Superhome.setupLed(); // default D1
  Superhome.setupWifi();
  Superhome.setupMQTT(mqttServer);
  Superhome.setupRf();    // default D3
  Superhome.setupRelay(); // default D4
  Superhome.setupOTA();
}

void loop()
{
  // make sure we stay connected to wifi
  Superhome.connectWifi();

  // make sure we stay connected to mqtt
  Superhome.connnectMQTT();

  // watch for ota update requests
  Superhome.loopOTA(ssid, password);
}
