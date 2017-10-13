#include <Superhome.h>

// Set the Device ID
const char *deviceId = "office/controller";

// Get superhome class and give it the deviceId
Superhome superhome(deviceId);

// Wifi config - wonder if there is some way to obscure this.
const char *ssid = "****";
const char *password = "*****";
const char *mqttServer = "*****";

// pin assignments
//int relayPin = D4;
int redLedPin = 5;
int greenLedPin = 14;
int rfPin = 4;

// mqtt config
const char *statusTopic = "trips/controller/status";
const char *switchTopic = "trips/controller/switch";

// for status update debouncing
int lastCall = 0;                       // 0 so it gets called immediately
int statusUpdateFrequency = 60000 * 60; // 1 hour

// keypad setup
String keypadPassword = String("11");
int keypadPasswordLength = 2;

// setup a general function for callbacks - some hoop that need to be jumped through
// https://www.gammon.com.au/callbacks
typedef void (*GeneralFunction)();

// keypad callbacks
GeneralFunction keypadSuccessCallback;
GeneralFunction keypadFailureCallback;

void keypadSuccess()
{
  Serial.println("[KEYPAD] - Password Success");

  // send a toggle request to the server
  // it will send the switch the opposite state
  superhome.sendMQTT("server/switch", "{\"id\":\"7\"}");

  superhome.pulseLed(greenLedPin, 500, 4);
}

void keypadFailure()
{
  Serial.println("[KEYPAD][ERROR] - Password Failure");
  superhome.pulseLed(redLedPin, 100, 4);
}

void setup()
{
  superhome.setupSerial(115200);
  superhome.setupLed(redLedPin, false);
  superhome.setupLed(greenLedPin, true);
  superhome.setupWifi();
  superhome.setupMQTT(mqttServer);
  superhome.setupRf(rfPin, 202);
  //  superhome.setupRelay(relayPin);
  superhome.setupOTA();
  superhome.setupKeypad(keypadPassword, keypadPasswordLength);
  Serial.println(lastCall);
  Serial.println(lastCall + statusUpdateFrequency);
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

  keypadSuccessCallback = keypadSuccess;
  keypadFailureCallback = keypadFailure;
  superhome.handleKeypad(keypadSuccessCallback, keypadFailureCallback);

  // watch for ota update requests
  superhome.loopOTA();
}
