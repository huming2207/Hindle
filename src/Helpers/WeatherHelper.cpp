//
// Created by Ming Hu on 20/2/18.
//

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Configs/APIs.h>
#include <Configs/Defaults.h>
#include "WeatherHelper.h"

weather_t WeatherHelper::fetchWeather()
{
  HTTPClient httpClient;
  weather_t weatherInfo = {};

  // Prepare a new URL
  auto owmUrl = String(HINDLE_API_OWM_BASE)
      + "&q=" + HINDLE_DEFAULT_LOCATION
      + "&appid=" + HDNLIE_API_OWM_KEY;

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
  JsonObject& jsonObject = jsonBuffer.parseObject(httpClient.getString());

  // Detect JSON parsing error
  if(!jsonObject.success()) {
    log_e("Error: JSON data corrupted.");
    weatherInfo.httpStatus = -32767; // Set error code to int16 minimum value for now.
    httpClient.end();
    jsonBuffer.clear();
    return weatherInfo;
  }

  // Put data to info struct
  weatherInfo.currDescription = jsonObject["list"][0]["weather"][0]["main"];
  weatherInfo.currCode        = (uint8_t)jsonObject["list"][0]["weather"][0]["main"].as<String>().toInt();
  weatherInfo.currHighTemp    = jsonObject["list"][0]["main"]["temp_max"];
  weatherInfo.currLowTemp     = jsonObject["list"][0]["main"]["temp_min"];
  weatherInfo.currHumidity    = jsonObject["list"][0]["main"]["humidity"];
  weatherInfo.nextDescription = jsonObject["list"][7]["weather"][0]["main"];
  weatherInfo.nextCode        = (uint8_t)jsonObject["list"][7]["weather"][0]["main"].as<String>().toInt();
  weatherInfo.nextHighTemp    = jsonObject["list"][7]["main"]["temp_max"];
  weatherInfo.nextLowTemp     = jsonObject["list"][7]["main"]["temp_min"];
  weatherInfo.nextHumidity    = jsonObject["list"][7]["main"]["humidity"];

  httpClient.end();
  jsonBuffer.clear();
  return weatherInfo;
}

