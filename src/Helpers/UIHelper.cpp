//
// Created by Ming Hu on 14/2/18.
//

#include "UIHelper.h"

void UIHelper::init(U8G2_IL3820_V2_296X128_F_4W_SW_SPI *main_u8g2)
{
  u8g2 = main_u8g2;

  // U8g2 init
  u8g2->begin();

  // Enable support for CJK fonts
  u8g2->enableUTF8Print();
}

void UIHelper::updateContent()
{
  // Draw vertical line between date/time area and event area
  u8g2->clearBuffer();
  u8g2->drawVLine(100, 0, 128);

  // Print date
  u8g2->setFont(u8g2_font_helvR18_tf);
  u8g2->setCursor(0, 20);
  u8g2->print("Feb 14");
  u8g2->setFont(u8g2_font_helvR14_tf);
  u8g2->setCursor(0,40);
  u8g2->print("Wed 2018");

  // Print event
  u8g2->setCursor(110, 12);
  u8g2->setFont(u8g2_font_wqy15_t_gb2312);
  u8g2->print("Happy Valentine's Day!");
  u8g2->setCursor(110, 27);
  u8g2->setFont(u8g2_font_t0_14b_tf);
  u8g2->print("Today all day");

  // Send buffer
  u8g2->sendBuffer();
}
