#include <Wire.h>
#include "heltec.h"

#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
#define OLED_UPDATE_INTERVAL 500

int counter = 0;

void setup() {

  //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);

  SSD1306Wire* display = new SSD1306Wire(0x3c, SDA_OLED, SCL_OLED, RST_OLED, GEOMETRY_128_64);
  display->init();
  display->setContrast(100);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  //display->invertDisplay();


  display->drawString(10, 10, "Hola");
  //display->displayOn();
  display->display();

}

void loop() {

}

