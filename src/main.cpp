#include <WiFiUdp.h>
#include <FastLED.h>
#include "Command.hpp"
#include "WifiConfig.hpp"
#include "MemConfig.hpp"
#include "Mode.hpp"
#include "NtpClientMine.hpp"
#include <ArduinoOTA.h>
#include <ESPmDNS.h>


#define ESP32

//закоментировать если не нужно обновление по wifi
#define OTA_UPDATE
#ifdef OTA_UPDATE
//OTA UPDATE HOSTNAME AND AUTH PASSWORD
  #define OTA_HOSTNAME "ota_ledochka"
  #define OTA_PSSWRD "fuckyoubitch"
#endif
//WIFI AP SSID AND PASSWORD
#define AP_HOSTNAME "Ledochka"
#define AP_PSSWRD "FUCKYOUBITCH"


#define STRSWITCH(STR)      char _x[16]; strcpy(_x, STR); if (false) 
#define STRCASE(STR)        } else if (strcmp(_x, STR)==0){

TaskHandle_t taskCore0_h;
TaskHandle_t taskCore1_h;

WiFiUDP Udp;
Command cmd;
WifiConfig wifi;
MemConfig mem;
Mode mode;

Command_s command_s;
char msg[255];


void updateState(void);

void setupCore0 (void){}


void loopCore0(void){
  int timeToAlarm=isAlarm(30);
  if(timeToAlarm!=-1){
    mode.setBright(155 - timeToAlarm*5);
    delay(4000);
    mode.setMode(1);
  }
      
  ArduinoOTA.handle();
	byte packetSize = Udp.parsePacket();
  
  if (packetSize) {     // если что то прислали
    
    byte len = Udp.read(msg, 255);
    if (len > 0){
      msg[len] = 0;
      command_s = cmd.get_message(msg);
      updateState();
    }
  }
}

void setupCore1(void){
}

void loopCore1(void){
   mode.update();
}

void updateState(void){
if(!command_s.command.equals("")){

    printf("--------------------------------\n");
    printf("Command: [%s]\n",command_s.command.c_str());
	  printf("Data:    [%s]\n",command_s.data.c_str());


    STRSWITCH(command_s.command.c_str()){
      STRCASE ("Mode")
        mode.setMode(atoi(command_s.data.c_str()));
      
      STRCASE ("Bright")
        mode.setBright(atoi(command_s.data.c_str()));
      
      STRCASE ("PerMode")
        mode.setPersonPalette((byte *)(command_s.data.c_str()));
      
      STRCASE ("Delay")
        mode.setDelay(atoi(command_s.data.c_str()));
      
      STRCASE ("EndLed")
        mode.setNumbLeds(atoi(command_s.data.c_str()));  
      
      STRCASE ("StartLed")
        mode.setStartLed(atoi(command_s.data.c_str()));  
      
      STRCASE ("Blend")
        mode.setStartLed(atoi(command_s.data.c_str()));  

      STRCASE ("WifiAP") 
        wifi.wifiAP(AP_HOSTNAME,AP_PSSWRD);

      STRCASE ("WifiSTA") 
        wifi.wifiSTAFromEeprom();

      STRCASE ("SSID") 
        mem.setOffsetW(0);
        mem.WriteConf(command_s.data);
      
      STRCASE ("Password")
        mem.WriteConf(command_s.data);

      STRCASE ("Hours")
        setAlarmHours(atoi(command_s.data.c_str()));

      STRCASE ("Minutes")
        setAlarmMinutes(atoi(command_s.data.c_str()));

      STRCASE ("Alarm")
        setAlarm(atoi(command_s.data.c_str()));
	    }    
   }
   command_s.command = "";
}

void taskCore0( void * pvParameters ){
  Serial.print("Task0 running on core ");
  Serial.println(xPortGetCoreID());
  setupCore0(); 
  for(;;){
    loopCore0();
    delay (300);
  }
}

void taskCore1( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  setupCore1();
  for(;;){
    loopCore1();
  }
}

  void ota_update(){
  #ifdef OTA_UPDATE
    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PSSWRD);
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
      else // U_SPIFFS
      type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
  #endif
  }

void setup() {
  //set monitor speed
  Serial.begin(115200); 
  //allocate memory for WIFI SSID and Password
  EEPROM.begin(64);

  //if esp cant connect to wifi
  if(!wifi.wifiSTAFromEeprom())
    //switch to WIFI AP
		wifi.wifiAP(AP_HOSTNAME,AP_PSSWRD);
  //begin udp protocol
	Udp.begin(2390);
  //config ota update ifdef OTA_UPDATE
  ota_update();  
  //init ntp time
  timeInit(3);
 
  
  //Task for core0
  xTaskCreatePinnedToCore(
                    taskCore0,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &taskCore0_h,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //Task for core1
  xTaskCreatePinnedToCore(
                    taskCore1,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &taskCore1_h,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
  delay(500); 
}

void loop() {}