#include "User.h"

using namespace std;

User::User() {
	this->loggedIn = false;
}

User::User(stringstream& s) {
	stringstream ss;
	string newLoginName, newPassword, newInstitution, newAreas;

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

	if (!getline(s, newAreas, ','))
		cout << "Error" << endl;

	istringstream iss(newAreas);
	string newArea;
	while (getline(iss, newArea, ';')) {
		this->areas.push_back(newArea);
	}

	//9999 is just a random big number of months, so it can be bigger than 5 years
	this->dataPay = 9999;
	this->loggedIn = false;
	this->quota = false;

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

void User::login() {
	if (loggedIn == false)
		loggedIn = true;
	else
		cout << "ERROR: You are already Logged In! " << endl;
}

void User::logout() {
	if (loggedIn == true)
		loggedIn = false;
	else
		cout << "ERROR: You are already Logged out! " << endl;
}

bool User::getLoggedIn() {
	return loggedIn;
}

vector <string> User::getVectorAreas(){
	return areas;
}
