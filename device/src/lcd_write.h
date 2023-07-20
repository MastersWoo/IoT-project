#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>

#define SOIL_MOISTURE_THRESHOLD 70

unsigned long previousMillis = 0;
const unsigned long interval = 5000; 

const int LCD_ADDRESS = 0x27;
const int LCD_ROWS = 2;
const int LCD_COLS = 16;


// LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS, 21, 22);

void lcd_init() {
  Wire.begin();

  lcd.init();
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();
  lcd.clear();
}

void checkJsonFormat(const char* sensor_data) {
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, sensor_data);

  if (error) {
    Serial.print("JSON parsing error: ");
    Serial.println(error.c_str());
      return;
  }
}

void lcd_display_data(const String& sensor_data) {
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    StaticJsonDocument<256> doc;

    float temperature = doc["temperature"].as<float>();
    float humidity = doc["humidity"].as<float>();
    int soil_moisture_reading = doc["soil_moisture"].as<int>();

    Serial.print("Temper: ");
    Serial.println(temperature);
    Serial.print("Humid: ");
    Serial.println(humidity);
    Serial.print("Soil: ");
    Serial.println(soil_moisture_reading);

    static int currentDataIndex = 0;
    static const int numDataPoints = 3;
    static const int rowMapping[numDataPoints] = {1, 0, 1};

    lcd.clear();
    
    lcd.setCursor(0, rowMapping[currentDataIndex]);
    if (currentDataIndex == 0) {
      lcd.print("Temper: ");
      lcd.print(temperature);
      lcd.print((char)223);
      lcd.print("C");
    } else if (currentDataIndex == 1) {
      lcd.print("Humid: ");
      lcd.print(humidity);
      lcd.print("%");
    } else if (currentDataIndex == 2) {
      lcd.print("Soil: ");
      lcd.print(soil_moisture_reading);
    }

    currentDataIndex = (currentDataIndex + 1) % numDataPoints;
  }
}