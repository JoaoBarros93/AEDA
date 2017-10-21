#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;


class User{
private:
	string loginName;
	string password;
	string institution;
	bool isLoggedIn = false;
	int monthsLastPaid;
public:
	User(stringstream& s);
	string getLoginName();
	string getPassword();
	string getInstitution();
	void login();

};



#endif /* USER_H_ */
