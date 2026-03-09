#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//U8G2_ST7305_168X384_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 17, /* dc=*/ 20, /* reset=*/ 15);

U8G2_ST7305_300X400_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 6, /* reset=*/ 10);

void setup() {
u8g2.begin(); 
}

void loop() {
  u8g2.firstPage();
  do {
    u8g2.drawFrame(1,1, 298,398);    
    u8g2.drawLine(0,0,23,23);
    u8g2.drawLine(0+24,0,23+24,47);    
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(5,60,"Hello World!");
    u8g2.drawStr(5,80,"Hello World!");

  } while ( u8g2.nextPage() );
  delay(1000);
}
