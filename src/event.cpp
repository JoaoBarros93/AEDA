#include "event.h"

EventSummerSchool::EventSummerSchool(User user, string local, string title, Date date, string area, int support, vector<User> formers, vector<User> promoters) {
	this->userCreated = user;
	this->local = local;
	this->date = date;
	this->title = title;
	this->formers = formers;
	this->area = area;
	this->support=support;
	this->usersPromoted=promoters;
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

int EventSummerSchool::getSupport(){
	return support;
}

vector<User> EventSummerSchool::getUsersPromoted(){
	return usersPromoted;
}

void EventSummerSchool::insertPromoter(User user){
	bool find = 0, created=0;

	if(userCreated.getLoginName()==user.getLoginName())
		created=1;

	for(unsigned int i = 0;i<usersPromoted.size();i++){
		if(usersPromoted[i].getLoginName()==user.getLoginName())
			find=1;
	}

	if(find==0 && created==0){
		cout << "Thank you! You promoted this event! " << endl;
		usersPromoted.push_back(user);
	}
	else if(created==1)
		cout << "Sorry! You cannot promote an event you created " << endl;
	else if(find==1)
		cout << "Sorry! You already promoted this event " << endl;
}

void EventSummerSchool::setSupport(int newSup){
	this->support=newSup;
}

EventConference::EventConference(User user, string local, string title, Date date, string area, int support, int numberPeople, vector<User> promoters) {
	this->userCreated = user;
	this->local = local;
	this->date = date;
	this->title = title;
	this->numberPeople = numberPeople;
	this->area = area;
	this->support=support;
	this->usersPromoted=promoters;
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

int EventConference::getSupport(){
	return support;
}

vector<User> EventConference::getUsersPromoted(){
	return usersPromoted;
}

void EventConference::insertPromoter(User user){
	bool find = 0, created=0;

	if(userCreated.getLoginName()==user.getLoginName())
		created=1;

	for(unsigned int i = 0;i<usersPromoted.size();i++){
		if(usersPromoted[i].getLoginName()==user.getLoginName())
			find=1;
	}

	if(find==0 && created==0){
		cout << "Thank you! You promoted this event! " << endl;
		usersPromoted.push_back(user);
	}
	else if(created==1)
		cout << "Sorry! You cannot promote an event you created " << endl;
	else if(find==1)
		cout << "Sorry! You already promoted this event " << endl;
}

void EventConference::setSupport(int newSup){
	this->support=newSup;
}
