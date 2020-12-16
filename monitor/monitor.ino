#include <SPI.h>
#include <Wire.h>
#include <ArduinoLowPower.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_AHTX0 aht;

//  Variables
const int LED13 = 13;
float temp_min;
float temp_max;
float humidity_min;
float humidity_max;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  display.dim(true);

  display.setTextColor(SSD1306_WHITE);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("System start, running...");
  display.display();
  temp_min = 100.0;
  temp_max = -100.0;
  humidity_min = 100.0;
  humidity_max = 0.0;
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  temp_min = min(temp_min, temp.temperature);
  temp_max = max(temp_max, temp.temperature);
  humidity_min = min(humidity_min, humidity.relative_humidity);
  humidity_max = max(humidity_max, humidity.relative_humidity);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(String(temp_min, 1) + " " + String(temp_max, 1) + " | " + String(humidity_min, 1) + " " + String(humidity_max, 1));
  display.setTextSize(2);
  display.setCursor(5, 15);
  display.println(String(temp.temperature, 1) + "  " + String(humidity.relative_humidity, 1));
  display.display();

  LowPower.deepSleep(5000);
}
