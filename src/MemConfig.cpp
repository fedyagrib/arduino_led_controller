#include "MemConfig.hpp"

MemConfig::MemConfig(){
    Serial.println("MemConfig::MemConfig()");
    offsetW = 0;
    offsetR = 0;
}

MemConfig::~MemConfig(){
}

void MemConfig::setOffsetW(byte value){
    offsetW=value;
}

void MemConfig::setOffsetR(byte value){
    offsetR=value;
}

void MemConfig::WriteConf(String word) {
  byte sizeWord = word.length();
  
  EEPROM.write(offsetW, sizeWord);
  offsetW++;

  for (byte i = 0; i < sizeWord; i++) {
    EEPROM.write(offsetW, word[i]);
    offsetW++;
    //temp++;
  }

  EEPROM.commit();
}

String MemConfig::ReadConf() {
  byte sizeData = EEPROM.read(offsetR);
  offsetR++;
  char word[sizeData+1];
  char* temp=word;

  for (int i = 0; i < sizeData; i++) {
    *temp = EEPROM.read(offsetR);
    offsetR++;
    temp++;
  }
  *temp='\0';
  Serial.printf("EEPROM %s\n",word);

  return word;
}
