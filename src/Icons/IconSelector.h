//
// Created by Ming Hu on 22/2/18.
//

#ifndef HINDLE_ICONSELECTOR_H
#define HINDLE_ICONSELECTOR_H

#include <cstdint>

#include "Icons/resources/sunny.h"
#include "Icons/resources/few_clouds.h"
#include "Icons/resources/cloudy.h"
#include "Icons/resources/broken_cloud.h"
#include "Icons/resources/rainy.h"
#include "Icons/resources/light_rain.h"
#include "Icons/resources/thunderstorm.h"
#include "Icons/resources/mist.h"
#include "Icons/resources/unknown.h"

class IconSelector
{
 public:
  static const uint8_t * selectWeatherIcon(uint8_t icon);
};

#endif //HINDLE_ICONSELECTOR_H
