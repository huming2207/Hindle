//
// Created by Ming Hu on 20/2/18.
//

#ifndef HINDLE_WEATHERHELPERH
#define HINDLE_WEATHERHELPERH

#include <cstdint>

typedef struct WeatherInfo
{
  String brief;
  int16_t highTemp;
  int16_t lowTemp;
  uint8_t humidity;
  uint8_t statusCode;
  int16_t httpStatus;
} weather_t;

class Weather
{
 public:
  static weather_t fetchWeather();
};


#endif //HINDLE_WEATHERHELPERH
