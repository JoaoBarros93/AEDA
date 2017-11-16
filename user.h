#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <ctime>
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
	char status; //c=contributor, s=subscriber; i=inactive
	int sent;
	int received;
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
	char getStatus();
	vector <Area> getVectorAreas();
	vector <string> getVectorAreasString();
	Date getTodayDate();
	int getTodayDay();
	int getTodayMonth();
	int getTodayYear();
	int getSent();
	int getReceived();
	void insertArea(Area newArea);
	void setDatePay(Date date);
	void setStatus(char newStatus);
	void setReceived(int newReceived);
	void setSent(int newSent);
	void login();
	void logout();
	void printAreas();
	Area stringToArea(string areaString, vector<Area > areas);
};

#endif /* USER_H_ */
