/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"

void setup() {
  setupSerial(115200);

  setupWifi();

  Serial.println("Setup done");
}

void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  scanForNetworks();
  
  // Wait a bit before scanning again
  delay(5000);
}

// FUNCTIONS
void setupSerial(int baud) {
  Serial.begin(baud);
  Serial.println("Serial Connected");
  delay(10);
}

void setupWifi() {
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  // give wifi time to setup
  delay(100);
}

void scanForNetworks() {
  int n = WiFi.scanNetworks();
  if(n == 0) {
    Serial.println("[ERROR] - No Networks Found");
  } else {
    Serial.print(n);
    Serial.println(" Networks Found");

    // attempt to connect to networks
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");
}