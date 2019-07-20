//#define ESP8266
#define ESP32

#ifdef ESP8266
	#include <ESP8266WiFi.h>
#endif
#ifdef ESP32
	#include <WiFi.h>
#endif

#include "Arduino.h"

class WifiConfig{
private:
   
public:
    WifiConfig();
    ~WifiConfig();
    bool wifiSTA(const char *ssid, const char *password);
    void wifiAP();
};