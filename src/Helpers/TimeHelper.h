//
// Created by Ming Hu on 17/2/18.
//

#ifndef HINDLE_TIMEHELPER_H
#define HINDLE_TIMEHELPER_H

class TimeHelper
{
 public:
  static bool setTime();
  static time_t parseIsoTimeStr(const char *timeStr);
};

#endif //HINDLE_TIMEHELPER_H
