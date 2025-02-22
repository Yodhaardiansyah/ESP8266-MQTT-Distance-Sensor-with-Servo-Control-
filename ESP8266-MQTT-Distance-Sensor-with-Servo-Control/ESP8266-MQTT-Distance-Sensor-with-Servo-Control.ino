/*
  Project: ESP8266 MQTT Distance Sensor with Servo Control
  Description: This program connects an ESP8266 to WiFi and an MQTT broker.
               It measures distance using an ultrasonic sensor and publishes the data to MQTT.
               It also controls a servo motor based on received MQTT messages.
  
  Author: Yodha Ardiansyah
  Website: https://arunovasi.my.id
  GitHub: https://github.com/Yodhaardiansyah
  Version: 1.0
  License: MIT
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// Define pins
const int trigPin = D5;
const int echoPin = D6;
const int servoPin = D3;

// WiFi credentials (Replace with your actual credentials)
const char* ssid = "YOUR_WIFI_SSID";         
const char* password = "YOUR_WIFI_PASSWORD"; 

// MQTT broker configuration (Replace with your actual credentials)
const char* mqttServer = "YOUR_MQTT_BROKER"; 
const int mqttPort = 1883;
const char* mqttUser = "YOUR_MQTT_USERNAME"; 
const char* mqttPassword = "YOUR_MQTT_PASSWORD";

// MQTT topics
const char* distanceTopic = "sensor/distance";
const char* servoAngleTopic = "sensor/servo";

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  connectToWiFi();

  // Configure MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);

  // Configure pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo
  servo.attach(servoPin);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Measure distance and publish it
  long distance = measureDistance();
  publishDistance(distance);

  delay(1000); // Adjust the delay as needed
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("connected!");

      // Subscribe to the servo angle topic
      client.subscribe(servoAngleTopic);
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println(topic);

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("Payload: " + message);

  // Process servo angle command
  if (String(topic) == servoAngleTopic) {
    int angle = message.toInt();
    if (angle >= 0 && angle <= 180) {
      servo.write(angle);
      Serial.println("Servo angle set to: " + String(angle));
    } else {
      Serial.println("Invalid angle received!");
    }
  }
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

void publishDistance(long distance) {
  char msg[50];
  sprintf(msg, "%ld", distance);

  Serial.print("Publishing distance: ");
  Serial.println(msg);

  client.publish(distanceTopic, msg);
}
