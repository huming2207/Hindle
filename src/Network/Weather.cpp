//
// Created by Ming Hu on 20/2/18.
//

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Configs/APIs.h>
#include <Configs/Defaults.h>
#include "Weather.h"

weather_t Weather::fetchWeather()
{
  HTTPClient httpClient;
  weather_t weatherInfo = {};

  // Prepare a new URL
  auto owmUrl = String(HINDLE_API_OWM_BASE)
      + "&q=" + HINDLE_DEFAULT_LOCATION
      + "&appid=" + HINDLE_API_OWM_KEY;

  httpClient.begin(owmUrl);

  // Perform request and grab the result
  int httpStatus = httpClient.GET();

  // Detect error
  if(httpStatus < 0) {
    log_e("Error: failed to access OpenWeatherMap API, return code %d!", httpStatus);

    httpClient.end();
    return weatherInfo;
  }

  // Grab the string and parse json
  log_i("Finished downloading JSON data, prepare to parse...");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& jsonObject = jsonBuffer.parseObject(httpClient.getStream());

  // Detect JSON parsing error
  if(!jsonObject.success()) {
    log_e("Error: JSON data corrupted.");
    weatherInfo.httpStatus = -32767; // Set error code to int16 minimum value for now.
    httpClient.end();
    jsonBuffer.clear();
    return weatherInfo;
  }

  // Put data to info struct
  weatherInfo.brief = jsonObject["list"][0]["weather"][0]["main"];
  weatherInfo.statusCode        = (uint8_t)jsonObject["list"][0]["weather"][0]["icon"].as<String>().toInt();
  weatherInfo.highTemp    = jsonObject["list"][0]["main"]["temp_max"];
  weatherInfo.lowTemp     = jsonObject["list"][0]["main"]["temp_min"];
  weatherInfo.humidity    = jsonObject["list"][0]["main"]["humidity"];

  httpClient.end();
  jsonBuffer.clear();
  return weatherInfo;
}

