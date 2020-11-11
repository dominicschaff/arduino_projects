#include <SPI.h>
#include "epd4in2.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Starting...");
  Epd epd;

  if (epd.Init() != 0) {
    Serial.println("e-Paper init failed");
    return;
  }
	//Serial.print(UNCOLORED);
  /* This clears the SRAM of the e-paper display */
  epd.ClearFrame();

  unsigned char image[1500];
  Paint paint(image, 400, 28);
//  paint.SetRotate(ROTATE_90);

  // 8 => 79 : Kind of too small
  // 12 => 57 : Seems like good general text for close up
  // 16 => 36 : seem like good for "normal sized tetxt
  // 20 => 28 : Large text
  // 24 => 23 : Good size for heading text

  paint.Clear(UNCOLORED);
  // No more than 23 characteres
  paint.DrawStringAt(0, 0, "Info Screen        1/30", &Font24, COLORED);
  paint.DrawRectangle(0, 20, 400, 21, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());

//  paint.SetHeight(12);

  // we can do 20 lines
  do_poem(paint, epd);
//  do_contact(paint, epd);
  epd.DisplayFrame();
  /* Deep sleep */
  epd.Sleep();
}

void do_poem(Paint paint, Epd epd) {
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "To see a World in a Grain of Sand", &Font12, COLORED);
  paint.DrawStringAt(0, 14, "And a Heaven in a Wild Flower", &Font12, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 0, 80, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Hold Infinity in the palm of your hand", &Font12, COLORED);
  paint.DrawStringAt(0, 14, "And Eternity in an hour", &Font12, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 0, 108, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "                                 Nothing is true", &Font12, COLORED);
  paint.DrawStringAt(0, 14, "                                 Everything is permitted", &Font12, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 0, 200, paint.GetWidth(), paint.GetHeight());


void loop() {
  // put your main code here, to run repeatedly:

}
