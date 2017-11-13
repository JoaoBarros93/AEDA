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
#include "user.h"
#include "area.h"
#include "date.h"
#include "event.h"

using namespace std;

class APIC{
private:
	User userLogged;
	vector<User > users;
	vector<Area > areas;
	vector<EventSummerSchool > eventsSS;
	vector<EventConference > eventsC;
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
	void insertEventSS(EventSummerSchool newEventSS);
	void insertEventC(EventConference newEventC);
	void searchUser();
	void searchEventByArea();
	void searchUserByArea();
	void searchUserBySubArea();
	void printUsers();
	void printUsersComplete();
	void printAreasFull();
	void printAreasSiglas();
	void printSubAreasUser();
	void printSubArea(string area);
	void printEventsComplete();
	void printEventsC();
	void printEventsSS();
	bool checkArea(string area);
	bool checkSubArea(string subArea);
	bool findSemicolon(string stringToSearch);
	void payQuota(APIC apic);
	void createEvent(APIC apic);
	void createSummerSchool(APIC apic);
	void createConference(APIC apic);
	void stringToUpper(string &s);
	void promoteEvent(APIC apic);
	void updateEventSupportC(EventConference eventC);
	void updateEventSupportSS(EventSummerSchool eventS);
	void loadUsers();
	void loadAreas();
	void loadEventsSS();
	void loadEventsC();
	void writeEventsSS();
	void writeEventsC();
	EventSummerSchool readSummerSchool(stringstream& s);
	EventConference readConference(stringstream& s);
	void menu1(APIC apic);
	void menu2(APIC apic);
	void menuSearch(APIC apic);
	void menuEvents(APIC apic);
};

#endif /* APIC_H_ */
