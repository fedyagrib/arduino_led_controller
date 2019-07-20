#include "Arduino.h"
#include <EEPROM.h>

class MemConfig
{
private:
    byte offsetW = 0; //offset in EEPROM for write
    byte offsetR = 0;//offset in EEPROM for read
    
public:
    MemConfig();
    ~MemConfig();

    void setOffsetW(byte value);
    void setOffsetR(byte value);

    String ReadConf();
    void WriteConf(char* word);
};