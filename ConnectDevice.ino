#include "EspMQTTClient.h"

EspMQTTClient client(
  "network",
  "dan1sw1network",
  "45.147.177.9",  // MQTT Broker server ip
  "MQTTUsername",   // Can be omitted if not needed
  "MQTTPassword",   // Can be omitted if not needed
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello Computer");

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "temperature" and display received message to Serial
  client.subscribe("temperature_result", [](const String & payload) {
    Serial.println(payload);
  });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  /*client.subscribe("temperature_result", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });*/

  // Отправка сообщения на сервер
  client.publish("temperature", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  // Выполнение инструкции после определённого времени
  client.executeDelayed(5 * 1000, []() {
    client.publish("temperature", "This is a message sent 5 seconds later");
  });
}

void loop()
{
  delay(500);
  client.loop();
  client.publish("temperature", "This is a message in loop"); 
}
