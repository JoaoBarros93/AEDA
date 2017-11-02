#ifndef APIC_H_
#define APIC_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cctype>
#include <algorithm>
#include <ctime>
#include "User.h"
#include "Area.h"
#include "date.h"

using namespace std;

class APIC{
private:
	User userLogged;
	vector<User > users;
	vector<Area > areas;
	bool userLoggedStatus = userLogged.getLoggedIn();
public:
	APIC();
	bool regist(APIC apic);
	bool login(int n, APIC apic);
	User getUserLogged();
	bool getStatus();
	int getTodayDay();
	int getTodayMonth();
	int getTodayYear();
	Date getTodayDate();
	void setUserLogged(User userLogged);
	void insertUser(User newuser);
	void insertArea(Area newArea);
	void searchUser();
	void searchUserByArea();
	void searchUserBySubArea();
	void printUsers();
	void printUsersComplete();
	void printAreasFull();
	void printAreasSiglas();
	void printSubAreasUser();
	void printSubArea(string area);
	bool checkArea(string area);
	bool checkSubArea(string subArea);
	bool findSemicolon(string stringToSearch);
	void payQuota();
	void stringToUpper(string &s);
	void menu1(APIC apic);
	void menu2(APIC apic);
};


#endif /* APIC_H_ */
