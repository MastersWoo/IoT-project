#include "sensor_control.h"

#define DHT11PIN 16
#define DHT_TYPE DHT11
#define JSON_DATA 500
#define SENSOR_CYCLE_MS 5000
#define SOIL_MOISTURE_PIN 33

unsigned long t1=0;
int soil_moisture_reading=0;
DHT dht(DHT11PIN, DHT_TYPE);



void sensor_setup() {
    dht.begin();
}

void read_Sensor_Data(char* sensor_data) {
    if(millis()-t1 > SENSOR_CYCLE_MS) {
        t1= millis();
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        soil_moisture_reading = map(analogRead(SOIL_MOISTURE_PIN), 1023, 0, 0, 100);

        StaticJsonDocument<256> tem_doc;
        tem_doc["temper"] = String(temperature, 1);

        char tem_jsondata[JSON_DATA];
        serializeJson(tem_doc, tem_jsondata);


        StaticJsonDocument<256> hum_doc;
        hum_doc["humid"] = String(humidity, 0);

        char hum_jsondata[JSON_DATA];
        serializeJson(hum_doc, hum_jsondata);

        StaticJsonDocument<256> soil_doc;
        soil_doc["soil"] = String(soil_moisture_reading);

        char soil_jsondata[JSON_DATA];
        serializeJson(soil_doc, soil_jsondata);

        strcpy(sensor_data, tem_jsondata);
        strcat(sensor_data, ",");
        strcat(sensor_data, hum_jsondata);
        strcat(sensor_data, ",");
        strcat(sensor_data, soil_jsondata);
    }   
}
