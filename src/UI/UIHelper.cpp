//
// Created by Ming Hu on 14/2/18.
//
#include <ctime>
#include <Network/Ptv.h>

#include "UIHelper.h"
#include "Network/Weather.h"
#include "Icons/IconSelector.h"

void UIHelper::init(U8G2_IL3820_V2_296X128_F_4W_SW_SPI *main_u8g2)
{
  u8g2 = main_u8g2;

  // U8g2 init
  u8g2->begin();

  // Enable support for CJK fonts
  u8g2->enableUTF8Print();

  // Draw vertical line between date/time area and event area
  u8g2->clearBuffer();
  u8g2->drawVLine(112, 0, 128);
}

void UIHelper::updateSyncTime()
{
  char timeBuf[60] = {'\0'};

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
  // 3 hour forecast
  u8g2->setFont(u8g2_font_wqy12_t_gb2312);
  u8g2->setCursor(40,15);
  u8g2->printf("%s", weather->brief);
  u8g2->setCursor(40,27);
  u8g2->printf("%d/%d°C %d%%", weather->lowTemp, weather->highTemp, weather->humidity);
  u8g2->drawXBM(0, 0, 32, 32, IconSelector::selectWeatherIcon(weather->statusCode));

  u8g2->sendBuffer();
}

void UIHelper::updatePtv(transport_t *transport)
{
  char timeBuf[60] = {'\0'};

  u8g2->setFont(u8g2_font_wqy12_t_gb2312);
  u8g2->setCursor(0,40);
  u8g2->printf("Platform %d", transport->firstPlatform);
  u8g2->setCursor(0,53);

  strftime(timeBuf, 60, "at %D %R", &transport->firstTime);
  u8g2->print(timeBuf);

  u8g2->sendBuffer();
}
