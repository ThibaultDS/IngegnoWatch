
//#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

//U8G2_SSD1305_128X64_ADAFRUIT_F_2ND_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1305_128X64_ADAFRUIT_F_HW_I2C u8g2(U8G2_R0);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

void setup(void) {
  u8g2.begin();
}

void loop(void) {

  String Test = "test";
  u8g2.clearBuffer();         // clear the internal memory
  //u8g2.setFont(u8g2_font_crox4hb_tr); // choose a suitable font
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  u8g2.drawStr(10,10,Test.c_str());  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);  
}

