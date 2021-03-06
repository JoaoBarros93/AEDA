#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include "user.h"

using namespace std;

class Message {
private:
	User userSent;
	Date todayDate;
	string msg;
	vector<User> usersReceived;

public:
	Message(User userSent, Date date, string msg,vector<User> usersReceived);
	string getMessage();
	vector<User> getUsersReceived();
	User getUserSent();
	Date getDate();

};


#endif /* MESSAGE_H_ */
