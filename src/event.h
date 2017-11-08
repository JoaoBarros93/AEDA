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
	string local, title, area;
	Date date;
	unsigned int numberPeople;
	vector<User> usersPromoted;
public:
	EventConference(User user, string local, string title, Date date, string area, int numberPeople);
	User getUserCreated();
	string getLocal();
	string getTitle();
	Date getDate();
	string getArea();
	int getNumberPeople();

};

class EventSummerSchool{
private:
	User userCreated;
	string local, title, area;
	Date date;
	vector<User> usersPromoted;
	vector<User> formers;
public:
	EventSummerSchool(User user, string local, string title, Date date, string area, vector<User> formers);
	User getUserCreated();
	string getLocal();
	string getTitle();
	Date getDate();
	string getArea();
	vector<User > getFormers();
};


#endif /* EVENT_H_ */
