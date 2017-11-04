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
	Event(User user,string local,Date date, char type, string title);
};

class EventConference : public Event{
private:
	unsigned int numberPeople;
public:
	EventConference(unsigned int numberPeople, User user,string local, Date date, char type, string title);
};

class EventSummerSchool : public Event{
private:
	vector<User> formers;
public:
	EventSummerSchool(vector<User> formers, User user,string local, Date date, char type, string title);
};


#endif /* EVENT_H_ */
