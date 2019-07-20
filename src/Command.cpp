#include "Command.hpp"

Command::Command(){
    Serial.println("Command::Command()");
    p_wifi  = new WifiConfig();
    p_mem   = new MemConfig();
    p_mode  = new Mode();
}

Command::~Command(){ 
    delete p_wifi;
    delete p_mem;
    delete p_mode;
}

void Command::printCommand(void){
    Serial.printf("Command: [%c]\n", command_s->command);
    Serial.printf("Data:    [%s]\n", command_s->data);
}

void Command::setCommand(Command_s * command){
    command_s = command;
}

void Command::data2Struct(void){
    Serial.println("------------------------------------");
    printCommand();

    switch (command_s->command)
    {
    case ('A'):
        Serial.println("exe command: create Wifi Access Point");
        p_wifi->wifiAP();
        break;

    case ('B'):
        Serial.println("exe command: setBrightness(empty)");
        p_mode->setBright(command_s->data[0]);
        break;

    case ('C'):
        Serial.println("exe command: setColor");
        p_mode->setRgb((Rgb_s *)command_s->data);
        break;

    case ('M'):
        Serial.println("exe command: changeMode");
        p_mode->setMode(command_s->data[0]);
        break;

    case ('P'):
        Serial.println("exe command: WritePassword");
        p_mem->WriteConf(command_s->data);
        break;

    case ('S'):
        Serial.println("exe command: WriteSSID");
        p_mem->setOffsetW(0);
        p_mem->WriteConf(command_s->data);
        break;

    default:
        break;
    }
    
}