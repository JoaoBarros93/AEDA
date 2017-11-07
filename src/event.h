#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <string>
#include "user.h"
#include "date.h"


using namespace std;

class EventConference {
private:
	User userCreated;
	string local;
	string title;
	Date date;
	vector<User> usersPromoted;
	char type;
	unsigned int numberPeople;
	vector<User> promoting;
public:
	EventConference(stringstream& s);
	EventConference(char type, User user, string local, string title, Date date, int numberPeople);
};

class EventSummerSchool{
private:
	User userCreated;
	string local;
	string title;
	Date date;
	vector<User> usersPromoted;
	char type;
	vector<User> formers;
	vector<User> promoting;
public:
	EventSummerSchool(char type, User user, string local, string title, Date date, vector<User> formers);
	vector<User > getFormers();
	string getTitle();
};


#endif /* EVENT_H_ */
