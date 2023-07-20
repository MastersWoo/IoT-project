#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <string.h>
#include "wifi_mqtt.h"
#include "sensor_control.h"


#define JSON_DATA 500
#define pump_relay 23

bool motor_running = false;

void order_callback(char *topic, byte *payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) {
        if (isPrintable(payload[i])) {
            message += (char)payload[i];
        }
    }

    message.trim();

    Serial.print("Received message: ");
    Serial.println(message);

    String motor_topic = "cmd/" + device_id + "/motor";
    const char* motor_topic_cstr = motor_topic.c_str();

    if (strcmp(topic, motor_topic_cstr) == 0) {
        if (message.equals("run")) {
            Serial.println("Motor running");
            digitalWrite(pump_relay, LOW);
            motor_running = true;
        } else if (message.equals("stop")) {
            Serial.println("Motor stopped");
            digitalWrite(pump_relay, HIGH);
            motor_running = false;
        }
    }
   
}

void setup() {
    Serial.begin(115200);
    mqtt_setup();
    sensor_setup();
    
    device_id = String(WiFi.macAddress());

    Serial.setDebugOutput(true);
    client.setCallback(order_callback);
    client.subscribe("cmd/device_id/motor");
    
    pinMode(pump_relay,OUTPUT);

    digitalWrite(pump_relay, HIGH); 

    Serial.println(F("DHTxx test!"));
    dht.begin();
}


void loop() {
    mqtt_loop();

    if (!motor_running) {
        char sensor_data[200];
        read_Sensor_Data(sensor_data);
        String connection_device_id = String(WiFi.macAddress());
        
        StaticJsonDocument<512> doc;
        doc["connection_device_id"] = connection_device_id;
        doc["sensor_data"] = sensor_data;

        char json_object[512];
        size_t length = serializeJson(doc, json_object, sizeof(json_object));

        Serial.println(json_object);
        String data_topic = "data/" + device_id + "/sensor_data";
        const char* data_topic_cstr = data_topic.c_str();
        client.publish(data_topic_cstr, json_object, length);        
    }
    

    delay(5000);
  
}
