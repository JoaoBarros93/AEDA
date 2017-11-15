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
	int support; //0=no 1=yes
public:
	EventConference(User user, string local, string title, Date date, string area, int supported, int numberPeople);
	User getUserCreated();
	string getLocal();
	string getTitle();
	Date getDate();
	string getArea();
	int getNumberPeople();
	int getSupport();
	void insertPromoter(User user);
};

class EventSummerSchool{
private:
	User userCreated;
	string local, title, area;
	Date date;
	vector<User> usersPromoted;
	vector<User> formers;
	int support; //0=no 1=yes
public:
	EventSummerSchool(User user, string local, string title, Date date, string area, int supported, vector<User> formers);
	User getUserCreated();
	string getLocal();
	string getTitle();
	Date getDate();
	string getArea();
	vector<User > getFormers();
	int getSupport();
	void insertPromoter(User user);
};


#endif /* EVENT_H_ */
