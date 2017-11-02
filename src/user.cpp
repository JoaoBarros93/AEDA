#include "User.h"

using namespace std;

User::User() {
	this->loggedIn = false;
}

User::User(stringstream& s, vector<Area> areas) {
	stringstream ss;
	string newLoginName, newPassword, newInstitution, newAreas, newDateString;

	//read login
	if (!getline(s, newLoginName, ';'))
		cout << "Error getting login name" << endl;
	ss << newLoginName;
	ss >> loginName;
	ss.clear();
	this->loginName = loginName;

	//read password
	if (!getline(s, newPassword, ';'))
		cout << "Error getting password" << endl;
	ss << newPassword;
	ss >> password;
	ss.clear();
	this->password = password;

	//read institution
	if (!getline(s, newInstitution, ';'))
		cout << "Error getting institution" << endl;
	ss << newInstitution;
	ss >> institution;
	ss.clear();
	this->institution = institution;

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error getting date" << endl;
	ss << newDateString;
	ss >> dateString;
	ss.clear();
	this->dateString = dateString;
	Date newDate(newDateString);
	this->datePay=newDate;

	//read all areas
	if (!getline(s, newAreas, ','))
		cout << "Error getting area" << endl;
	istringstream iss(newAreas);
	string newArea;
	while (getline(iss, newArea, ';')) {
		this->areasString.push_back(newArea);
	}
	for (unsigned int i = 0; i < areasString.size(); i++) {
		Area newArea;
		newArea = stringToArea(areasString[i], areas);
		insertArea(newArea);
	}

	//starts logged off
	this->loggedIn = false;
}

//GET FUNCTIONS
string User::getLoginName() {
	return loginName;
}

string User::getPassword() {
	return password;
}

string User::getInstitution() {
	return institution;
}

Date User::getDatePay() {
	return datePay;
}

bool User::getLoggedIn() {
	return loggedIn;
}

vector<string> User::getVectorAreasString() {
	return areasString;
}

vector<Area> User::getVectorAreas() {
	return areas;
}

string User::getDateString(){
	return dateString;
}

//SET FUNCTIONS
void User::insertArea(Area newArea) {
	this->areas.push_back(newArea);
}

void User::setDatePay(Date date) {
	this->datePay = date;
}

//PRINT FUNCTIONS
void User::printAreas() {
	for (unsigned int i = 0; i < areasString.size(); i++) {
		cout << areasString[i] << endl;
	}
}

//CONVERT FUNCTIONS
Area User::stringToArea(string areaString, vector<Area> areas) {

	vector<string> areaAndSub;
	string area, subarea;
	Area newArea;
	char str[5];
	strcpy(str, areaString.c_str());
	char* point;
	point = strtok(str, "-");

	while (point != NULL) {
		areaAndSub.push_back(point);
		point = strtok(NULL, "-");
	}

	for (unsigned int i = 0; i < areaAndSub.size(); i++) {
		if (i == 0) {
			area = areaAndSub[i];
			subarea = areaAndSub[i + 1];
		}
	}

	for (unsigned int i = 0; i < areas.size(); i++) {
		if (areas[i].getAreaNameSigla() == area
				&& areas[i].getSubAreaNameSigla() == subarea) {
			return areas[i];
		}
	}
	return newArea;
}

//OTHER FUNCTIONS
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

