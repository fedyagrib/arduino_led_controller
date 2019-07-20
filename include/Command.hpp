#include "WifiConfig.hpp"
#include "MemConfig.hpp"
#include "Mode.hpp"

struct Command_s{
    char command;
    char data[16];
};

class Command{
private:
    Command_s * command_s;

    WifiConfig  * p_wifi;
    MemConfig   * p_mem;
    Mode        * p_mode;
    
    void printCommand(void);

public:
 
    Command();
    ~Command();

    void setCommand(Command_s * command);
    Command_s * getCommand(void);
    void data2Struct(void);
};