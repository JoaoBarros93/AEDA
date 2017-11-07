#include "event.h"

Event::Event(char type, User user, string local, string title, Date date){
	this->userCreated=user;
	this->local=local;
	this->date=date;
	this->type=type;
	this->title=title;
}

EventConference::EventConference(char type, User user, string local, string title, Date date, int numberPeople):Event(type,user,local,title,date){
	this->numberPeople=numberPeople;
}

EventSummerSchool::EventSummerSchool(char type, User user, string local, string title, Date date, vector<User> formers):Event(type,user,local,title,date){
	this->formers=formers;
}
