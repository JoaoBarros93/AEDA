#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <regex>


using namespace std;

class Date{
private:
	int day, month, year;
public:
	Date();
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date(string dateString);
	int getDay();
	int getMonth();
	int getYear();
	int getTodayDay();
	int getTodayMonth();
	int getTodayYear();
	Date getTodayDate();
	void setDate(unsigned int day, unsigned int month, unsigned int year);
	unsigned int GiveMonthDays(unsigned int month, unsigned int year);
	bool isBissesto(unsigned int ano);
	bool isSub(Date dateToCompare);
	bool isContributor(Date dateToCompare);
	bool isFuture();
	inline bool isNumber(const int & c);
	void printDate();

};

#endif /* DATE_H_ */
