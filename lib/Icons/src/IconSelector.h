//
// Created by Ming Hu on 22/2/18.
//

#ifndef HINDLE_ICONSELECTOR_H
#define HINDLE_ICONSELECTOR_H

#include <cstdint>

#include "resources/sunny.h"
#include "resources/few_clouds.h"
#include "resources/cloudy.h"
#include "resources/broken_cloud.h"
#include "resources/rainy.h"
#include "resources/light_rain.h"
#include "resources/thunderstorm.h"
#include "resources/mist.h"
#include "resources/unknown.h"

class IconSelector
{
 public:
  static const char * selectWeatherIcon(uint8_t icon);
};

#endif //HINDLE_ICONSELECTOR_H
