//
// Created by Ming Hu on 17/2/18.
//

#include <ctime>

#include <Arduino.h>
#include <Configs/Defaults.h>
#include <Configs/APIs.h>

#include "Time.h"

bool SntpTime::setTime()
{
  // FIXME: use NVRAM settings
  configTzTime(HINDLE_DEFAULT_TIMEZONE,
               HINDLE_NTP_SERVER_0,
               HINDLE_NTP_SERVER_1);
}

time_t SntpTime::parseIsoTimeStr(const char *timeStr)
{
  if(!timeStr) {
    return false;
  }

  struct std::tm tm;
  strptime(timeStr, "%Y%m%dT%H%M%S", &tm);
  return mktime(&tm);
}

