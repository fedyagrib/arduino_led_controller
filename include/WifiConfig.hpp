#ifndef WIFI_CONFIG_HPP_
#define WIFI_CONFIG_HPP_

//#define ESP8266
#define ESP32

#ifdef ESP8266
	#include <ESP8266WiFi.h>
#endif
#ifdef ESP32
	#include <WiFi.h>
#endif

#include "Arduino.h"
#include "MemConfig.hpp"

class WifiConfig{
private:
   MemConfig * p_mem;

public:
    WifiConfig();
    ~WifiConfig();
    bool wifiSTA(const char *ssid, const char *password);
    void wifiAP();
    bool wifiSTAFromEeprom();
};

#endif /* WIFI_CONFIG_HPP_ */