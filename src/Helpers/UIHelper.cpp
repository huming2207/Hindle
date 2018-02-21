//
// Created by Ming Hu on 14/2/18.
//

#include "UIHelper.h"
#include "WeatherHelper.h"
#include <ctime>

void UIHelper::init(U8G2_IL3820_V2_296X128_F_4W_SW_SPI *main_u8g2)
{
  u8g2 = main_u8g2;

  // U8g2 init
  u8g2->begin();

  // Enable support for CJK fonts
  u8g2->enableUTF8Print();
}

void UIHelper::updateSyncTime()
{
  char timeBuf[60] = {'\0'};

  // Draw vertical line between date/time area and event area
  u8g2->clearBuffer();
  u8g2->drawVLine(100, 0, 128);

  // Get time
  struct std::tm curr_time;
  if(!getLocalTime(&curr_time)) {
    log_e("Failed to retrieve system time!");
  } else {
    // Print date
    u8g2->setFont(u8g2_font_courR08_tf);
    u8g2->setCursor(0, 128);
    memset(&timeBuf, '\0', 60);
    strftime(timeBuf, 60, "%D %R", &curr_time);
    u8g2->print(timeBuf);
  }
}

void UIHelper::updateWeather(weather_t *weather)
{
  u8g2->setFont(u8g2_font_wqy12_t_gb2312);
  u8g2->setCursor(0,20);
  u8g2->printf("3hr: %s", weather->currDescription);
  u8g2->setCursor(0,40);
  u8g2->printf("%d-%d ℃, %d %%", weather->currLowTemp, weather->currHighTemp, weather->currHumidity);
  u8g2->sendBuffer();
}

