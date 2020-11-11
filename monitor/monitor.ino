#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//  Variables
const int LED13 = 13;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextColor(SSD1306_WHITE);

  drawText("Screen Started, awaiting...", true);
}

void drawText(String line, bool clearScreen) {
  if (clearScreen) {
    display.clearDisplay();
  }
  display.setCursor(0, 0);
  display.println(line);
  display.display();
}
String a;
void loop() {
  while(Serial.available()) {
    a = Serial.readStringUntil('\n');
    Serial.println(a);
    drawText(a, true);
  }
}
