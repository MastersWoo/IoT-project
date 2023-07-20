#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>

#define DHT11PIN 16
#define DHT_TYPE DHT11
#define JSON_DATA 500
#define SENSOR_CYCLE_MS 5000
#define SOIL_MOISTURE_PIN 33

extern unsigned long t1;
extern int soil_moisture_reading;
extern DHT dht;

void sensor_setup();
void read_Sensor_Data(char* sensor_data);

#endif
