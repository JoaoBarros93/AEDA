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
#include "message.h"
#include "exceptions.h"

using namespace std;

class APIC{
private:
	User userLogged;
	vector<User > users;
	vector<Area > areas;
	vector<EventSummerSchool > eventsSS;
	vector<EventConference > eventsC;
	vector<Message> messages;
	bool userLoggedStatus = userLogged.getLoggedIn();
public:
	APIC();

	//GET FUNCTIONS
	User getUserLogged();
	bool getStatus();
	int getTodayDay();
	int getTodayMonth();
	int getTodayYear();
	Date getTodayDate();

	//SET FUNCTIONS
	void setUserLogged(User userLogged);
	void insertUser(User newuser);
	void insertArea(Area newArea);
	void insertEventSS(EventSummerSchool newEventSS);
	void insertEventC(EventConference newEventC);
	void insertMessage(Message newMessage);

	//PRINT FUNCTIONS
	void printUsers();
	void printUsersComplete();
	void printAreasFull();
	void printAreasAndSub();
	void printAreasSiglas();
	void printSubAreasUser();
	void printSubArea(string area);
	void printEventsC();
	void printEventsSS();
	void printMessage(User receiver);
	void printEvents();

	//SEARCH FUNCTIONS
	void searchUser();
	void searchEventByArea();
	void searchUserByArea();
	void searchUserBySubArea();

	//CHECK FUNCTIONS
	bool checkArea(string area);
	bool checkSubArea(string subArea);
	bool checkStatusC(APIC apic); //true if user logged is contributer
	bool checkStatusI(APIC apic); //true if user logged is inactive

	//CREATE FUNCTIONS
	void createEvent(APIC apic);
	void createSummerSchool(APIC apic);
	void createConference(APIC apic);
	void createMessage(APIC apic);

	//LOAD FUNCTIONS
	void loadUsers();
	void loadAreas();
	void loadEventsSS();
	void loadEventsC();
	void loadMessages();

	//READ FUNCTIONS
	EventSummerSchool readSummerSchool(stringstream& s);
	EventConference readConference(stringstream& s);
	Message readMessage(stringstream& s);

	//WRITE FUNCTIONS
	void writeEventsSS();
	void writeEventsC();

	//MENU FUNCTIONS
	void menu1(APIC apic);
	void menu2(APIC apic);
	void menuSearch(APIC apic);
	void menuEvents(APIC apic);
	void menuMessages(APIC apic);

	//OTHER FUNCTIONS
	bool findSemicolon(string stringToSearch); //returns true if string has semicolon
	void payQuota(APIC apic); //sets pay date to today date
	void stringToUpper(string &s);
	void promoteEvent(APIC apic);
	bool regist(APIC apic);
	bool login(int n, APIC apic);
	void updateEventSupportC(EventConference eventC);
	void updateEventSupportSS(EventSummerSchool eventS);

};

#endif /* APIC_H_ */
