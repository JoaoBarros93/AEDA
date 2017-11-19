#include "User.h"

using namespace std;

User::User() {
	this->loggedIn = false;
}

User::User(stringstream& s, vector<Area> areas) {
	stringstream ss;
	string newLoginName, newPassword, newInstitution, newAreas, newDateString, sentString, receivedString;

	//read login
	if (!getline(s, newLoginName, ';'))
		cout << "Error reading login name" << endl;
	ss << newLoginName;
	ss >> loginName;
	ss.clear();
	this->loginName = loginName;

	//read password
	if (!getline(s, newPassword, ';'))
		cout << "Error reading password" << endl;
	ss << newPassword;
	ss >> password;
	ss.clear();
	this->password = password;

	//read institution
	if (!getline(s, newInstitution, ';'))
		cout << "Error reading institution " << endl;
	ss << newInstitution;
	ss >> institution;
	ss.clear();
	this->institution = institution;

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error reading date " << endl;
	ss << newDateString;
	ss >> dateString;
	ss.clear();
	this->dateString = dateString;
	Date newDate(newDateString);
	this->datePay=newDate;

	//read sent
	if (!getline(s, sentString, ';'))
		cout << "Error reading sent " << endl;
	ss << sentString;
	ss >> sentString;
	ss.clear();
	this->sent = stoi(sentString);

	//read received
	if (!getline(s, receivedString, ';'))
		cout << "Error reading received " << endl;
	ss << receivedString;
	ss >> receivedString;
	ss.clear();
	this->received = stoi(receivedString);

	//read all areas
	if (!getline(s, newAreas, ','))
		cout << "Error reading area " << endl;
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

	Date todayDate = getTodayDate();

	if(this->datePay.isContributor(todayDate))this->status='c';
	else if(this->datePay.isSub(todayDate))this->status='s';
	else this->status='i';

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

char User::getStatus(){
	return status;
}

Date User::getTodayDate() {
int day = getTodayDay();
int month = getTodayMonth();
int year = getTodayYear();
Date todayDate(day, month, year);
return todayDate;
}

int User::getTodayDay() {
time_t now;
struct tm nowLocal;
now = time(NULL);
nowLocal = *localtime(&now);
return nowLocal.tm_mday;
}

int User::getTodayMonth() {
time_t now;
struct tm nowLocal;
now = time(NULL);
nowLocal = *localtime(&now);
return nowLocal.tm_mon + 1;
}

int User::getTodayYear() {
time_t now;
struct tm nowLocal;
now = time(NULL);
nowLocal = *localtime(&now);
return nowLocal.tm_year + 1900;
}

int User::getSent(){
	return sent;
}

int User::getReceived(){
	return received;
}
//SET FUNCTIONS
void User::insertArea(Area newArea) {
	this->areas.push_back(newArea);
}

void User::setDatePay(Date date) {
	this->datePay = date;
}

void User::setStatus(char newStatus){
	this->status=newStatus;
}

void User::setReceived(int newReceived){
	this->received=newReceived;
}

void User::setSent(int newSent){
	this->sent=newSent;
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

