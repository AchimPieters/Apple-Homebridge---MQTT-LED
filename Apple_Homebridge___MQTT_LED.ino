/* Project name: Apple Homebridge – MQTT LED
   Project URI: https://www.studiopieters.nl/?p=3866&preview=true
   Description: Apple Homebridge Turn On / OFF A LED OVER MQTT
   Version: 0.2.1
   License: MIT  */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid =  "Your_SSID";    // cannot be longer than 32 characters!
const char *pass =  "Your_PASS";    //

// Update these with values suitable for your network.
IPAddress server(192, 168, 1, 10);

#define BUFFER_SIZE 100


void callback(const MQTT::Publish& pub) {
  pinMode(2, OUTPUT);



  // check if the message in On or Off
  if (pub.payload_string() == "On") {
    // turn LED on:
    digitalWrite(2, HIGH);
    Serial.println(pub.payload_string());
  } else {
    // turn LED off:
    digitalWrite(2, LOW);
    Serial.println(pub.payload_string());
  }
}

WiFiClient wclient;
PubSubClient client(wclient, server);

void setup() {
  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("arduinoClient")) {
        client.set_callback(callback);
        client.subscribe("InTopic"); // change InTopic to your Topic description
      }
    }

    if (client.connected())
      client.loop();
  }

}
