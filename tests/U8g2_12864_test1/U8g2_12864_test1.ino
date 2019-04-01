#include <U8g2lib.h> //version 2.24.3
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Connect display to SDA = D2 and SCL = D1
// Select correct initialization for your screen, select from https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Here init for a 4pin 128x64 OLED done via software I2C
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1305_128X64_ADAFRUIT_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();

  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(10,10,"Hallo");
  u8g2.sendBuffer();
  delay(200);
  u8g2.clearBuffer();
}

void loop() {
  u8g2.drawStr(10,15,"1 Hallo");
  u8g2.sendBuffer();
  delay(200);
}
