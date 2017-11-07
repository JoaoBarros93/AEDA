#include "event.h"

EventConference::EventConference(char type, User user, string local, string title, Date date, int numberPeople){
	this->userCreated=user;
	this->local=local;
	this->date=date;
	this->type=type;
	this->title=title;
	this->numberPeople=numberPeople;
}

EventSummerSchool::EventSummerSchool(char type, User user, string local, string title, Date date, vector<User> formers){
	this->userCreated=user;
	this->local=local;
	this->date=date;
	this->type=type;
	this->title=title;
	this->formers=formers;
}

vector<User > EventSummerSchool::getFormers(){
	return formers;
}

string EventSummerSchool::getTitle(){
	return title;
}
