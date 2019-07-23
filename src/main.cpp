#include <Arduino.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "Command.hpp"
#include "WifiConfig.hpp"
#include "MemConfig.hpp"
#include "Mode.hpp"



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


void setupCore0 (void){
  if(!wifi.wifiSTAFromEeprom())
		wifi.wifiAP();
	Udp.begin(2390);
}

void loopCore0(void){
	byte packetSize = Udp.parsePacket();
  
  if (packetSize) {     // если что то прислали
    
    byte len = Udp.read(msg, 255);
    if (len > 0){
      msg[len] = 0;
      printf("commamd [%s]\n",msg);
      command_s = cmd.get_message(msg);
    }
  }
}

void setupCore1(void){
}

void loopCore1(void){
   if(!command_s.command.equals("")){

    printf("----------------------------------------\n");
    printf("Command: [%s]\n",command_s.command.c_str());
	  printf("Data:    [%s]\n",command_s.data.c_str());


    STRSWITCH(command_s.command.c_str()){
      STRCASE ("Mode")
        mode.setMode(atoi(command_s.data.c_str()));
      STRCASE ("Bright")
        mode.setBright(atoi(command_s.data.c_str()));
      STRCASE ("Delay")
        mode.setDelay(atoi(command_s.data.c_str()));
      STRCASE ("NumLeds")
        mode.setNumbLeds(atoi(command_s.data.c_str()));  
      STRCASE ("SetStardLed")
        mode.setStartLed(atoi(command_s.data.c_str()));  
      STRCASE ("SetBlending")
        mode.setStartLed(atoi(command_s.data.c_str()));  

      STRCASE ("WifiAP") 
        wifi.wifiAP();
      STRCASE ("WifiSTA") 
        wifi.wifiSTAFromEeprom();
        command_s.command = "";
      STRCASE ("SSID") 
        mem.setOffsetW(0);
        mem.WriteConf(command_s.data);
        command_s.command = "";
      STRCASE ("Password")
        mem.WriteConf(command_s.data);
        command_s.command = "";
	    }    
   }
   command_s.command = "";
   mode.update();
}

void taskCore0( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  setupCore0(); 
  for(;;){
    loopCore0();
    delay (500);
  }
}

void taskCore1( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  setupCore1();
  for(;;){
    loopCore1();
  }
}

void setup() {
  Serial.begin(115200); 
  EEPROM.begin(64);
  
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    taskCore0,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &taskCore0_h,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
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