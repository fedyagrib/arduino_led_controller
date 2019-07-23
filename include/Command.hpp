#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include "Arduino.h"

struct Command_s{
	String command;
	String data;
};

class Command{
private:

    String msgStart = "<msg>";
    String msgEnd	= "</msg>";

    String cmdStart = "<cmd>";
    String cmdEnd 	= "</cmd>";

    String dataStart = "<data>";
    String dataEnd 	 = "</data>";

    String lengthStart 	= "<l>";
    String lengthEnd 	= "</l>";

    void checkMark(bool * start, String defword, String msg, int * index_msg);
    String readValue(bool * end, String defword, String msg, int * index_msg);

public:
    Command();
    ~Command();

    Command_s get_message(String msg);
};

#endif /* COMMAND_HPP_ */