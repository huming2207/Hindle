//
// Created by Ming Hu on 17/2/18.
//

#ifndef HINDLE_TIMEHELPER_H
#define HINDLE_TIMEHELPER_H

class SntpTime
{
 public:
  static bool setTime();
  static time_t parseTimeStr(String timeStr);
  static struct std::tm parseTimeStrToTm(String timeStr);
};

#endif //HINDLE_TIMEHELPER_H
