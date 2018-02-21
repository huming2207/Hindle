//
// Created by Ming Hu on 21/2/18.
//

#ifndef HINDLE_APIS_H
#define HINDLE_APIS_H

/**
 * OpenWeatherMap weather forecast API
 *
 * There are two more parameters to go:
 *  - q:     Location in "City,Country" style (e.g. "Melbourne,AU" or "Shenzhen,CN")
 *  - appid: API key in HDNLIE_API_OWM_KEY
 */
#define HINDLE_API_OWM_BASE "http://api.openweathermap.org/data/2.5/forecast?cnt=8&units=metric"

/* OpenWeatherMap key, grab your own for free at their site please. */
#define HDNLIE_API_OWM_KEY "GRAB_YOUR_OWN"

/* NTP Servers, use Aliyun's server as a backup in mainland China */
#define HINDLE_NTP_SERVER_0 "time.apple.com"
#define HINDLE_NTP_SERVER_1 "time.pool.aliyun.com"


#endif //HINDLE_APIS_H
