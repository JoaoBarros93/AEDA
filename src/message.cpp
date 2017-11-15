#include "message.h"

Message::Message(User userSent, Date date, string msg,vector<User> usersReceived){
	this->userSent = userSent;
	this->todayDate=date;
	this->msg=msg;
	this->usersReceived=usersReceived;
}
