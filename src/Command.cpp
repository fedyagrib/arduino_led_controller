#include "Command.hpp"

Command::Command(){}

Command::~Command(){}

void Command::checkMark(bool * start, String defword, String msg, int * index_msg){
	int defSize = defword.length();
	int msgSize = msg.length();

	int i = * index_msg;
	bool enable = * start;

	int def_i   = 0;
	int check_i = 0;

	for (; i < msgSize; i++){
		if(!enable){
			if(def_i < defSize){
				if(msg[i] == defword[def_i]){
					check_i++;
				}
				def_i++;
				
			}else if(check_i == defSize){
				enable = true;
				break;
			}
		}
	}

	* start = enable;
	* index_msg = i;
}

String Command::readValue(bool * end, String defword, String msg, int * index_msg) {
	String result = "";

	int defSize = defword.length();
	int msgSize = msg.length();

	int i = *index_msg;
	bool enable = *end;

	int def_i = 0;
	int check_i = 0;

	for (; i < msgSize; i++) {
		if (!enable) {
			if (msg[i] != '<') {
				result += msg[i];
			} else {
				i--;
				enable = true;
			}
		} else {
			if (def_i < defSize) {
				if (msg[i] == defword[def_i]) {
					check_i++;
				}
				def_i++;
			} else {
				if (check_i == defSize) {
					break;
				} else {
					result = "";
				}
			}
		}
	}
	*end = enable;
	*index_msg = i;
	return result;
}

Command_s Command::get_message(String msg){

	Command_s result;

	bool msgStartCheck = false;
	bool cmdStartCheck = false;
	bool cmdEndCheck = false;
	bool dataStartCheck = false;
	bool dataEndCheck = false;
	bool msgEndCheck = false;

	int msgSize= msg.length();

	for (int i = 0; i < msgSize; i++){

		//проверка на начало сообщения
		if(!msgStartCheck){
			checkMark(&msgStartCheck, msgStart, msg, &i);
		}

		//если между <msg> </msg>
		if(msgStartCheck && !cmdEndCheck){
			//check cmd
			checkMark(&cmdStartCheck, cmdStart, msg, &i);
			result.command = readValue(&cmdEndCheck, cmdEnd, msg, &i);
		}

		if(msgStartCheck && !dataEndCheck){
			//check data
			checkMark(&dataStartCheck, dataStart, msg, &i);
			result.data = readValue(&dataEndCheck, dataEnd, msg, &i);
		}

		//если дошли до </msg>
		if(msgStartCheck && cmdEndCheck && dataEndCheck){
			readValue(&msgEndCheck, msgEnd, msg, &i);
		}
	}
    return result;

}