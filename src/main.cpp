//
// Created by Ming Hu on 29/1/18.
//

#include <Arduino.h>
#include <U8g2lib.h>

U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2(U8G2_R0, 22, 21, 17, 16, 2);

void setup()
{
  u8g2.begin();
  u8g2.initDisplay();
}

void loop()
{
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_wqy14_t_gb2312);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("世人千万种，浮云莫去求。");
  u8g2.setCursor(0, 30);
  u8g2.print("斯人若彩虹，遇上方知有。");
  u8g2.setCursor(0, 50);

  u8g2.setFont(u8g2_font_rosencrantz_nbp_tf);
  u8g2.println("Once in a while you find someone who's iridescent, ");
  u8g2.setCursor(0, 65);
  u8g2.println("and when you do, nothing will ever compare");
  u8g2.sendBuffer();
  delay(1000);
}