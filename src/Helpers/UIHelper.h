//
// Created by Ming Hu on 14/2/18.
//

#ifndef HINDLE_UIHELPER_H
#define HINDLE_UIHELPER_H

#include <U8g2lib.h>
#include "WeatherHelper.h"

class UIHelper
{
 public:
  void init(U8G2_IL3820_V2_296X128_F_4W_SW_SPI *main_u8g2);
  void updateSyncTime();
  void updateWeather(weather_t *weather);
 private:
  U8G2_IL3820_V2_296X128_F_4W_SW_SPI *u8g2;

};

#endif //HINDLE_UIHELPER_H
