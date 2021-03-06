//
// Created by Ming Hu on 29/1/18.
//

#include <Arduino.h>
#include <U8g2lib.h>
#include <UI/UIHelper.h>
#include <Network/SntpTime.h>
#include <WiFi.h>
#include <Network/Weather.h>
#include <Configs/APIs.h>

U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2(U8G2_R0, 22, 21, 17, 16, 2);

UIHelper helper;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(HINDLE_TEMP_WIFI_SSID, HINDLE_TEMP_WIFI_PASSWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("connected!");

  SntpTime::setTime();
  weather_t weather = Weather::fetchWeather();
  transport_t transport = Ptv::fetchTransportInfo();

  helper.init(&u8g2);
  helper.updateSyncTime();
  helper.updatePtv(&transport);
  helper.updateWeather(&weather);
}

void loop()
{
  // When user presses Ctrl-C, it should reboots.
  if(Serial.available() > 0) {
    if(Serial.read() == 3) {
      log_w("Will now restart!");
      ESP.restart();
    }
  }
}