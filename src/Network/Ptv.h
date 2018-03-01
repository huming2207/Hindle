//
// Created by Ming Hu on 22/2/18.
//

#ifndef HINDLE_PTV_H
#define HINDLE_PTV_H

#include <ctime>
#include <cstdint>
#include <WString.h>

/**
 * PTV API response
 *
 * Only parse estimated departure to save hardware resources
 * PTV punctuality normally sucks...
 */
typedef struct TransportInfo
{
  bool isSuccess;
  bool hasDisruption;
  uint8_t firstPlatform;
  uint8_t secondPlatform;
  struct std::tm firstTime;
  struct std::tm secondTime;
} transport_t;

class Ptv
{
 public:
  static transport_t fetchTransportInfo();
 private:
  static String calculateSignature(String queryPath, const char * apiKey);
};

#endif //HINDLE_PTV_H
