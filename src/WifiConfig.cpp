#include "WifiConfig.hpp"

WifiConfig::WifiConfig(){}
WifiConfig::~WifiConfig(){}

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
        if (tray > 30)
            return 0;
    }

    ip = WiFi.localIP();                                                                                                                                                                                                                                                                                                                                 
    ip[3] = 90;
    WiFi.config(ip, subnet, gateway, dns); //ip=xxx.xxx.xxx.90
    WiFi.mode(WIFI_STA);                   //WiFi mode station (connect to wifi router only
    Serial.print("STA local ip: ");
    Serial.println(WiFi.localIP());
    return 1;
}

void WifiConfig::wifiAP()
{
    Serial.println("Switching to Wifi AP...");
    WiFi.disconnect();
    WiFi.softAP("Ledochka", "FUCKYOUBITCH");
    Serial.print("Ap local ip: 192.168.4.1");
}
