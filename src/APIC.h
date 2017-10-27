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
#include "User.h"
#include "Area.h"

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
	void setUserLogged(User userLogged);
	void insertUser(User newuser);
	void insertArea(Area newArea);
	User getUserLogged();
	bool getStatus();
	void menu1(APIC apic);
	void menu2(APIC apic);
	bool findSemicolon(string stringToSearch);
	void printUsers();
	void printUsersComplete();
	void searchUser();
	void searchUserByArea();
	void searchUserBySubArea();
	void printAreasFull();
	void printAreasSiglas();
	void printSubAreasUser();
	void printSubArea(string area);
	bool checkArea(string area);
	bool checkSubArea(string subArea);
};


#endif /* APIC_H_ */
