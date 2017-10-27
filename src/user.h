#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include "area.h"

using namespace std;

class User{
private:
	string loginName;
	string password;
	string institution;
	bool loggedIn;
	bool quota;
	int dataPay;
	vector <string> areasString;
	vector <Area> areas;
public:
	User();
	User(stringstream& s,vector<Area > areas);
	string getLoginName();
	string getPassword();
	string getInstitution();
	bool getLoggedIn();
	vector <Area> getVectorAreas();
	vector <string> getVectorAreasString();
	void login();
	void logout();
	void printAreas();
	Area stringToArea(string areaString, vector<Area > areas);
	void insertArea(Area newArea);
};

#endif /* USER_H_ */
