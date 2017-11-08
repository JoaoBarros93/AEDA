#include "event.h"

EventSummerSchool::EventSummerSchool(User user, string local, string title, Date date, string area, vector<User> formers) {
	this->userCreated = user;
	this->local = local;
	this->date = date;
	this->title = title;
	this->formers = formers;
	this->area = area;
}



User EventSummerSchool::getUserCreated() {
	return userCreated;
}

string EventSummerSchool::getLocal(){
	return local;
}
string EventSummerSchool::getTitle() {
	return title;
}

Date EventSummerSchool::getDate(){
	return date;
}

string EventSummerSchool::getArea(){
	return area;
}

vector<User> EventSummerSchool::getFormers() {
	return formers;
}

EventConference::EventConference(User user, string local, string title, Date date, string area, int numberPeople) {
	this->userCreated = user;
	this->local = local;
	this->date = date;
	this->title = title;
	this->numberPeople = numberPeople;
	this->area = area;
}

User EventConference::getUserCreated() {
	return userCreated;
}

string EventConference::getLocal(){
	return local;
}

string EventConference::getTitle(){
	return title;
}

Date EventConference::getDate(){
	return date;
}

string EventConference::getArea(){
	return area;
}

int EventConference::getNumberPeople(){
	return numberPeople;
}
