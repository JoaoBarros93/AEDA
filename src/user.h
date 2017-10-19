#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>

using namespace std;


class User{
private:
	string loginName;
	string institution;
	int monthsLastPaid;
public:
	User(string name){
		loginName = name;
		//9999 months is just a random big number bigger than 5 years
		monthsLastPaid=9999;
	}
	string getLoginName();

};



#endif /* USER_H_ */
