//
// Created by Ming Hu on 29/1/18.
//

#include <Arduino.h>
#include <U8g2lib.h>
#include <Helpers/UIHelper.h>

U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2(U8G2_R0, 22, 21, 17, 16, 2);

UIHelper helper;

void setup()
{
  helper.init(&u8g2);
  helper.updateContent();
}

void loop()
{
  delay(1000);
}