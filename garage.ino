#include <Superhome.h>

// Set the Device ID
const char *deviceId = "garage/controller";

// Get superhome class and give it the deviceId
Superhome superhome(deviceId);

// Wifi config - wonder if there is some way to obscure this.
const char *ssid = "****";
const char *password = "****";
const char *mqttServer = "*****";

// pin assignments
int relayPin = 4;
//int redLedPin = 16;
int greenLedPin = 16;
int rfPin = 5;

// mqtt config
const char *statusTopic = "garage/controller/status";
const char *switchTopic = "garage/controller/switch";

// for status update debouncing
int lastCall = 0;                       // 0 so it gets called immediately
int statusUpdateFrequency = 60000 * 60; // 1 hour

void setup()
{
  superhome.setupSerial(115200);
  //  superhome.setupLed(redLedPin, false);
  superhome.setupLed(greenLedPin, true);
  superhome.setupWifi();
  superhome.setupMQTT(mqttServer);
  superhome.setupRf(rfPin, 202);
  superhome.setupRelay(relayPin);
  superhome.setupOTA();
}

void loop()
{
  // make sure we stay connected to wifi
  superhome.connectWifi(ssid, password);

  // make sure we stay connected to mqtt
  superhome.connectMQTT(statusTopic, switchTopic);

  // send an update request every so often
  int currentMillis = millis();
  if (lastCall + statusUpdateFrequency < currentMillis)
  {
    Serial.println("[MQTT] - sending status update");
    lastCall = currentMillis;
    superhome.sendMQTT(statusTopic, "{\"state\":\"online\"}");
  }

  // watch for ota update requests
  superhome.loopOTA();
}
