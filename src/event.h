#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <string>
#include "user.h"
#include "date.h"


using namespace std;

class Event{
private:
	User userCreated;
	string local;
	string title;
	Date date;
	vector<User> usersPromoted;
	char type;
public:
	Event(char type, User user, string local, string title, Date date);
};

class EventConference : public Event{
private:
	unsigned int numberPeople;
public:
	EventConference(char type, User user, string local, string title, Date date, int numberPeople);
};

class EventSummerSchool : public Event{
private:
	vector<User> formers;
public:
	EventSummerSchool(char type, User user, string local, string title, Date date, vector<User> formers);
};


#endif /* EVENT_H_ */
