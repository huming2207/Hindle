//
// Created by Ming Hu on 22/2/18.
//

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Configs/Defaults.h>
#include <Configs/APIs.h>
#include "Ptv.h"
#include "SntpTime.h"

transport_t Ptv::fetchTransportInfo()
{
  HTTPClient httpClient;

  // Prepare query path
  String queryPath = String("/v3/departures/route_type/")
                        + HINDLE_TEMP_PTV_ROUTE_TYPE //FIXME: specify parameters by NVRAM
                        + "/stop/"
                        + HINDLE_TEMP_PTV_STOP_ID    //FIXME: specify parameters by NVRAM
                        + "?max_results=1"           // One result only (to save RAM)
                        + "&devid="
                        + HINDLE_API_PTV_ID;

  // Grab the signature out, thanks.
  String signature = calculateSignature(queryPath, HINDLE_API_PTV_KEY);

  // Now it should be "/v3/departures/route_type/0/stop/11101?devid=100100"
  String fullUrl = String(HINDLE_API_PTV_BASE)
                      + queryPath
                      + "&signature="
                      + signature;
  log_i("Full URL: %s", fullUrl.c_str());
  httpClient.begin(fullUrl);

  // Finally, fire the HTTP client and JSON parser
  int httpStatus = httpClient.GET();

  // Detect error
  if(httpStatus < 0) {
    log_e("Error: failed to access PTV API, return code %d!", httpStatus);
    httpClient.end();
    transport_t transportInfo{};
    return transportInfo;
  }

  // Grab the string and parse json
  log_i("Finished downloading JSON data, prepare to parse...");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& jsonObject = jsonBuffer.parseObject(httpClient.getStream());

  // Detect JSON parsing error
  if(!jsonObject.success()) {
    log_e("Error: JSON data corrupted.");
    httpClient.end();
    jsonBuffer.clear();
    transport_t transportInfo{};
    return transportInfo;
  }

  // Sometimes estimated departure string can be null, so use scheduled (timetabled) time instead
  String firstTimeStr = jsonObject["departures"][0]["estimated_departure_utc"].as<String>();
  String secondTimeStr = jsonObject["departures"][1]["estimated_departure_utc"].as<String>();

  if(!firstTimeStr || firstTimeStr.length() < 1) {
    firstTimeStr = jsonObject["departures"][0]["scheduled_departure_utc"].as<String>();
  }

  if(!secondTimeStr || secondTimeStr.length() < 1) {
    secondTimeStr = jsonObject["departures"][1]["scheduled_departure_utc"].as<String>();
  }


  transport_t transportInfo = {
      .isSuccess = (jsonObject["status"]["health"].as<int>() == 1),
      .hasDisruption = (jsonObject["disruptions"].as<JsonArray&>().size() > 0),
      .firstPlatform = (uint8_t)jsonObject["departures"][0]["platform_number"].as<unsigned short>(),
      .secondPlatform = (uint8_t)jsonObject["departures"][1]["platform_number"].as<unsigned short>(),
      .firstTime = SntpTime::parseTimeStrToTm(firstTimeStr),
      .secondTime = SntpTime::parseTimeStrToTm(secondTimeStr),
  };

  httpClient.end();
  jsonBuffer.clear();
  return transportInfo;
}

/**
 * Calculate PTV API's signature
 * According to PTV API references
 *  "The signature value is a HMAC-SHA1 hash of the completed request
 *  (minus the base URL but including your user ID, known as “devid”)"
 *
 * ...so the query path should include API Developer ID, e.g. "/v3/departures/route_type/0/stop/11101?devid=100100"
 *
 * @param queryPath Mentioned above
 * @param apiKey Your API Developer Key
 * @return Signature, a 40-digit uppercase hex string.
 */
String Ptv::calculateSignature(String queryPath, const char * apiKey)
{
  log_i("Query URL path: %s", queryPath.c_str());
  unsigned char hashResult[20];
  memset(&hashResult, '\0', 20);

  // Calculate HMAC-SHA1 hash with mbedtls
  int ret = mbedtls_md_hmac(mbedtls_md_info_from_type(MBEDTLS_MD_SHA1),   // Type: HMAC-SHA1
                            (const uint8_t *)apiKey,                      // Key: API Key
                            strlen(apiKey),                               // Key size
                            (const unsigned char*)queryPath.c_str(),      // Data: PTV API query URL payload
                            queryPath.length(),                           // Data size
                            hashResult);                                  // Result to hashResult

  if(ret != 0) {
    log_e("Signature calculation failed, mbedtls returns a non-zero value: %d", ret);
    return String();
  }

  // Convert hash buffer to PTV API ref specific signature string
  String result;
  for (unsigned char hashBit : hashResult) {

    // Workaround for String() to HEX:
    // When a value smaller than 0x0f, it will not append 0 to it, which may causes error.
    if(hashBit <= 0xf) {
      result += "0";
      result += String(hashBit, HEX);
    } else {
      result += String(hashBit, HEX);
    }
  }

  // ...be aware that they are case sensitive
  result.toUpperCase();
  log_i("Query signature: %s", result.c_str());
  return result;
}
