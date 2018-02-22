//
// Created by Ming Hu on 22/2/18.
//

#include "IconSelector.h"


const char *IconSelector::selectWeatherIcon(uint8_t icon)
{
  switch(icon){
    case 1: return HINDLE_ICON_SUNNY;
    case 2: return HINDLE_ICON_FEW_CLOUDS;
    case 3: return HINDLE_ICON_CLOUDY;
    case 4: return HINDLE_ICON_BROKEN_CLOUD;
    case 9: return HINDLE_ICON_RAINY;
    case 10: return HINDLE_ICON_LIGHT_RAIN;
    case 11: return HINDLE_ICON_THUNDERSTORM;
    case 50: return HINDLE_ICON_MIST;
    default: return HINDLE_ICON_UNKNOWN;
  }
}
