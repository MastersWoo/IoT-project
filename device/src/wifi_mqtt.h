#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define JSON_DATA 500
#define SENSOR_DATA_TOPIC "data/device_id/sensor_data"
#define REGISTRATION_TOPIC "registration/device_id"  //registration_topic

WiFiClient espClient;
PubSubClient client(espClient);

const char *ssid = "SK_WiFiGIGA4C34_2.4G"; // wiFi Name
const char *password = "1701002144"; // wifi password
const char *mqtt_user = "elice"; //mqtt 브로커 id"
const char *mqtt_pass = "smartfarm"; //mqtt 브로커 password
const char *mqtt_server = "52.79.210.192";  // ip address

String device_id = "";
String motor_topic = "";
const char* MOTOR_ACT_TOPIC = "";


bool received_registration = false;

void check_registration();
void registration_callback(char* topic, byte* payload, unsigned int length);

void device_id_connect() {

  static int reconnect_delay = 1000;
  
  while (!client.connected()) {
    String connection_device_id = String(WiFi.macAddress());
    if (client.connect(connection_device_id.c_str(),mqtt_user,mqtt_pass)) {
      Serial.println("connected");
      Serial.print("Client ID: ");
      Serial.println(connection_device_id);
      device_id = connection_device_id;
      motor_topic = "cmd/" + device_id + "/motor";
      MOTOR_ACT_TOPIC = motor_topic.c_str();
      Serial.print("Subscribing to topic: ");
      Serial.println(MOTOR_ACT_TOPIC);
      client.subscribe(motor_topic.c_str());
      client.subscribe(REGISTRATION_TOPIC);
      reconnect_delay = 1000;
    } else {
      Serial.println(" try again");
      delay(reconnect_delay);
    }
  }
}

WiFiClient wifiClient;

void mqtt_setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connected");
    delay(1000);
  }
  
  client.setClient(wifiClient);
  client.setServer(mqtt_server, 1883);
  device_id_connect();
}



void mqtt_loop() {
  if (!client.connected()) {
    device_id_connect();
    while (!client.connected()) {
      if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
        Serial.println("Connected to MQTT Broker!!");
        check_registration();
      } else {
        Serial.print("Failed to connect to MQTT Broker, state: ");
        Serial.println(client.state());
        delay(1000);
        return;
      }
    }
  }

  Serial.println("Connected to MQTT Broker!");
  client.loop();
  
}



void wifi_mqtt_publish(char* jsondata) {
  client.publish(SENSOR_DATA_TOPIC, jsondata);
}

void pub_registration() {
  String connect_registration = "Registration request!";
  client.publish(REGISTRATION_TOPIC, connect_registration.c_str());
}

void registration_callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, REGISTRATION_TOPIC) == 0) {
    received_registration = true;
  }
}

void check_registration() {
  client.setCallback(registration_callback);
  client.subscribe(REGISTRATION_TOPIC);
  int try_registration_count = 0;
  while (try_registration_count < 3) {
    pub_registration();
    delay(1000);

    if (received_registration) {
      Serial.println("Device registered success");
      return;
    } else {
      try_registration_count++;
    }
  }
  Serial.println("Device registration unsuccess");
}



