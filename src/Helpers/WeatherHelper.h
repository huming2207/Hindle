//
// Created by Ming Hu on 20/2/18.
//

#ifndef HINDLE_WEATHERHELPERH
#define HINDLE_WEATHERHELPERH

#include <cstdint>

typedef struct WeatherInfo
{
  const char *currIcon;
  const char *nextIcon;
  const char *currDescription;
  const char *nextDescription;
  int16_t currHighTemp;
  int16_t nextHighTemp;
  int16_t currLowTemp;
  int16_t nextLowTemp;
  uint8_t currHumidity;
  uint8_t nextHumidity;
  uint8_t currCode;
  uint8_t nextCode;
  int16_t httpStatus;
} weather_t;

class WeatherHelper
{
 public:
  weather_t fetchWeather();
};


#endif //HINDLE_WEATHERHELPERH
