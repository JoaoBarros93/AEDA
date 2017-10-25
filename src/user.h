#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

class User{
private:
	string loginName;
	string password;
	string institution;
	bool loggedIn;
	bool quota;
	int dataPay;
	vector <string> areas;
public:
	User();
	User(stringstream& s);
	string getLoginName();
	string getPassword();
	string getInstitution();
	bool getLoggedIn();
	vector <string> getVectorAreas();
	void login();
	void logout();

};

#endif /* USER_H_ */
