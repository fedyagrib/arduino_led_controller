#include <WiFiUdp.h>
#include "Command.hpp"

WiFiUDP Udp;
Command *p_cmd;
WifiConfig * p_wifi;
MemConfig * p_mem;


bool wifiSTAFromEeprom()
{
  p_mem->setOffsetR(0);
  return p_wifi->wifiSTA(p_mem->ReadConf().c_str(), p_mem->ReadConf().c_str());
}

void setup()
{
  p_wifi = new WifiConfig();
  p_mem =new MemConfig();
  p_cmd = new Command();
  
  EEPROM.begin(34);
  Serial.begin(115200);
  if(!wifiSTAFromEeprom())
		p_wifi->wifiAP();
	Udp.begin(2390);
}

void loop()
{
   char cmd[17];
	byte packetSize = Udp.parsePacket();
  
  if (packetSize) {     // если что то прислали
    
    byte len = Udp.read(cmd, 17);
    if (len > 0){
      cmd[len] = 0;
      p_cmd->setCommand((Command_s *)cmd);
      p_cmd->data2Struct();
    }
  }

}