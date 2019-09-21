#include "WifiConfig.hpp"

WifiConfig::WifiConfig(){
    p_mem = new MemConfig();
}
WifiConfig::~WifiConfig(){
    delete p_mem;
}

bool WifiConfig::wifiSTA(const char *ssid, const char *password)
{
    Serial.println("Switching to Wifi STA...");
    //Static IP address configuration
    IPAddress ip;
    IPAddress gateway(192, 168, 43, 1); //IP Address of your WiFi Router (Gateway)
    IPAddress subnet(255, 255, 255, 0); //Subnet mask
    IPAddress dns(8, 8, 8, 8);          //DNS

    byte tray = 0;
#ifdef ESP32
    WiFi.disconnect(); //Prevent connecting to wifi based on previous configuration
#endif
#ifdef ESP8266
    WiFi.persistent(false);
    WiFi.disconnect(true);
#endif
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        tray++;
        delay(500);
        Serial.print(".");
        if (tray > 20)
            return 0;
    }

    ip = WiFi.localIP();                                                                                                                                                                                                                                                                                                                                 
    ip[3] = 90;
    WiFi.config(ip, WiFi.gatewayIP(), WiFi.subnetMask(), dns); //ip=192.168.xxx.90
    WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only)
    Serial.print("\nSTA local ip: ");
    Serial.println(WiFi.localIP());
    return 1;
}

void WifiConfig::wifiAP(const char ssid[], const char psswrd[])
{
    Serial.println("Switching to Wifi AP...");
    WiFi.disconnect();
    WiFi.softAP(ssid, psswrd);
    Serial.println("Ap local ip: 192.168.4.1");
}

bool WifiConfig::wifiSTAFromEeprom()
{
  p_mem->setOffsetR(0);
  return wifiSTA(p_mem->ReadConf().c_str(), p_mem->ReadConf().c_str());
}
