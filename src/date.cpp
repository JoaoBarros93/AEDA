#include "date.h"

Date::Date() {
	time_t t = time(0); // get time now
	struct tm * now = localtime(&t);
	setDate((now->tm_mday), (now->tm_mon + 1), (now->tm_year + 1900));
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	setDate(day, month, year);
}

Date::Date(string dateString) {

	vector<string> tokens;
	regex re("\\d+");


	sregex_token_iterator begin(dateString.begin(), dateString.end(), re), end;

	copy(begin, end, back_inserter(tokens));

	for(unsigned int i = 0;i<tokens.size();i++){
		if(i==0){
			this->day=stoi(tokens[i]);
			this->month=stoi(tokens[i+1]);
			this->year=stoi(tokens[i+2]);
		}
	}
}

int Date::getDay() {
	return day;
}

int Date::getMonth() {
	return month;
}

int Date::getYear() {
	return year;
}

void Date::setDate(unsigned int day, unsigned int month, unsigned int year) {
	if (month < 1 || month > 12)
		cout << "ERROR: Wrong month! ";
	unsigned int days = GiveMonthDays(month, year);
	if (days == 0 || day < 1 || day > days)
		cout << "ERROR: Wrong day! ";
	if (year < 2000)
		cout << "ERROR: Wrong year! ";

	this->day = day;
	this->month = month;
	this->year = year;
}

bool Date::isBissesto(unsigned int ano) {
	return (ano % 4 == 0 && ((ano % 100 != 0) || (ano % 400 == 0)));
}

unsigned int Date::GiveMonthDays(unsigned int month, unsigned int year) {
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 2:
		return isBissesto(year) ? 29 : 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 0; // false
	}
}

void Date::printDate() {
	cout << getDay() << "/" << getMonth() << "/" << getYear() << endl;
}
