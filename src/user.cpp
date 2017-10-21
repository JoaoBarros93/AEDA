#include "user.h"

using namespace std;

User::User(stringstream& s) {
	stringstream ss;
	string newLoginName, newPassword, newInstitution;

	if (!getline(s, newLoginName, ';'))
		cout << "Error" << endl;

	ss << newLoginName;
	ss >> loginName;
	ss.clear();
	this->loginName = loginName;

	if (!getline(s, newPassword, ';'))
		cout << "Error" << endl;

	ss << newPassword;
	ss >> password;
	ss.clear();
	this->password = password;

	if (!getline(s, newInstitution, ';'))
		cout << "Error" << endl;

	ss << newInstitution;
	ss >> institution;
	ss.clear();
	this->institution = institution;

	//9999 is just a random big number of months, so it can be bigger than 5 years
	this->monthsLastPaid = 9999;

}

string User::getLoginName() {
	return loginName;
}

string User::getPassword() {
	return password;
}

string User::getInstitution() {
	return institution;
}

void User::login(){
	isLoggedIn=true;
}
