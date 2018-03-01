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
#define HINDLE_API_OWM_KEY "GRAB_YOUR_OWN"

/* PTV API base URL */
#define HINDLE_API_PTV_BASE "http://timetableapi.ptv.vic.gov.au"

/* PTV API ID, should be a numeric string */
#define HINDLE_API_PTV_ID ""

/* PTV API Key, should be a UUID */
#define HINDLE_API_PTV_KEY ""

/* NTP Servers, use Aliyun's server as a backup in mainland China */
#define HINDLE_NTP_SERVER_0 "time.apple.com"
#define HINDLE_NTP_SERVER_1 "time.pool.aliyun.com"

/* FIXME: change to read NVRAM later */
#define HINDLE_TEMP_WIFI_SSID "go-grab-your-own"
#define HINDLE_TEMP_WIFI_PASSWD "who-the-hell-knows"
#define HINDLE_TEMP_PTV_ROUTE_TYPE "0"    // Type: metro train
#define HINDLE_TEMP_PTV_STOP_ID    "1000"

#endif //HINDLE_APIS_H
