/*
 * IRremoteESP8266: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 Sept, 2015
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009, Copyright 2009 Ken Shirriff, http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */

#include <IRremoteESP8266.h>

int RECV_PIN = D6; //an IR detector/demodulatord is connected to GPIO pin 2

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


void dump(decode_results *results) {
  if(results->value == 4294967295) {
    // ignore repeat codes
    return;
  }

  if(results->value == 3810010651) {
    Serial.println("POWER ON");
  } else {
    Serial.print(results->value);
    Serial.print(" = ");
    Serial.print(results->value, HEX);
    Serial.println();
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}
