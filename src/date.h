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
	void setDate(unsigned int day, unsigned int month, unsigned int year);
	unsigned int GiveMonthDays(unsigned int month, unsigned int year);
	bool isBissesto(unsigned int ano);
	void printDate();

};

#endif /* DATE_H_ */
