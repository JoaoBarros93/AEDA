#ifndef APIC_H_
#define APIC_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "User.h"

using namespace std;

class APIC{
private:
	User userLogged;
	vector<User > users;
	bool userLoggedStatus = userLogged.getLoggedIn();
public:
	APIC();
	bool regist(APIC apic);
	bool login(int n, APIC apic);
	void setUserLogged(User userLogged);
	void insertUser(User newuser);
	User getUserLogged();
	bool getStatus();
	void menu1(APIC apic);
	void menu2(APIC apic);
	bool findSemicolon(string stringToSearch);
	void printUsers();
	void printUsersComplete();
	void searchUser();
};


#endif /* APIC_H_ */
