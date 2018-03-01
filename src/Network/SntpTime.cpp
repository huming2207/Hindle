//
// Created by Ming Hu on 17/2/18.
//

#include <ctime>
#include <utility>

#include <Arduino.h>
#include <Configs/Defaults.h>
#include <Configs/APIs.h>

#include "SntpTime.h"

bool SntpTime::setTime()
{
  // FIXME: use NVRAM settings
  configTzTime(HINDLE_DEFAULT_TIMEZONE,
               HINDLE_NTP_SERVER_0,
               HINDLE_NTP_SERVER_1);
}

time_t SntpTime::parseIsoTimeStr(String timeStr)
{
  if(!timeStr) {
    return 0;
  }

  auto tm = SntpTime::parseTimeStrToTm(std::move(timeStr));
  return mktime(&tm);
}

struct std::tm SntpTime::parseTimeStrToTm(String timeStr)
{
  if(!timeStr) {
    struct std::tm emptyTm;
    return emptyTm;
  }

  struct std::tm tm;

  if(timeStr.indexOf("-") > 0) {
    strptime(timeStr.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm);
  } else {
    strptime(timeStr.c_str(), "%Y%m%dT%H%M%SZ", &tm);
  }

  return tm;
}

