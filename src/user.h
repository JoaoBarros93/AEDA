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
#include "date.h"

using namespace std;

class User{
private:
	string loginName;
	string password;
	string institution;
	string dateString;
	bool loggedIn;
	Date datePay;
	vector <string> areasString;
	vector <Area> areas;
public:
	User();
	User(stringstream& s,vector<Area > areas);
	string getLoginName();
	string getPassword();
	string getInstitution();
	bool getLoggedIn();
	Date getDatePay();
	string getDateString();
	vector <Area> getVectorAreas();
	vector <string> getVectorAreasString();
	void insertArea(Area newArea);
	void setDatePay(Date date);
	void login();
	void logout();
	void printAreas();
	Area stringToArea(string areaString, vector<Area > areas);
	Date stringToDate(string dateString);
	int stringToMonth(string dateString);
	int stringToYear(string dateString);
};

#endif /* USER_H_ */
