#include "event.h"

Event::Event(User user,string local,Date date,char type, string title){
	this->userCreated=user;
	this->local=local;
	this->date=date;
	this->type=type;
	this->title=title;
}

EventConference::EventConference(unsigned int numberPeople, User user,string local, Date date, char type, string title):Event(user,local,date,type,title){
	this->numberPeople=numberPeople;
}

EventSummerSchool::EventSummerSchool(vector<User> formers, User user,string local, Date date, char type,string title):Event(user,local,date,type,title){
	this->formers=formers;
}
