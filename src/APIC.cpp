#include "APIC.h"
using namespace std;

APIC::APIC() {

	//read areas file and populate areas vector
	loadAreas();

	//read users file and populate users vector
	loadUsers();

	//read events file and populate events vector
	loadEventsSS();
	loadEventsC();

	//read messages file and populate messages vector
	loadMessages();
}

/************************************************
******************GET FUNCTIONS******************
************************************************/
User APIC::getUserLogged() {
	return userLogged;
}

bool APIC::getStatus() {
	return userLoggedStatus;
}

Date APIC::getTodayDate() {
	int day = getTodayDay();
	int month = getTodayMonth();
	int year = getTodayYear();
	Date todayDate(day, month, year);
	return todayDate;
}

int APIC::getTodayDay() {
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);
	return nowLocal.tm_mday;
}

int APIC::getTodayMonth() {
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);
	return nowLocal.tm_mon + 1;
}

int APIC::getTodayYear() {
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);
	return nowLocal.tm_year + 1900;
}

/***************************************************
 *****************SET FUNCTIONS*********************
***************************************************/
void APIC::setUserLogged(User userLogged) {
	this->userLogged = userLogged;
}

void APIC::insertUser(User newuser) {
	users.push_back(newuser);
}

void APIC::insertArea(Area newArea) {
	areas.push_back(newArea);
}

void APIC::insertEventSS(EventSummerSchool newEventSS) {
	eventsSS.push_back(newEventSS);
}

void APIC::insertEventC(EventConference newEventC) {
	eventsC.push_back(newEventC);
}

void APIC::insertMessage(Message newMessage) {
	messages.push_back(newMessage);
}

/**************************************************
******************PRINT FUNCTIONS******************
**************************************************/
void APIC::printUsers() {
	cout << endl << "---All users--- " << endl;
	for (unsigned int i = 0; i < users.size(); i++) {
		cout << i+1 << ": " << users[i].getLoginName() << endl;
	}
}

void APIC::printUsersComplete() {
	cout << endl << "Complete info of all users: " << endl << endl;
	for (unsigned int i = 0; i < users.size(); i++) {
		cout << "----" << "User" << i + 1 << "----" << endl;
		cout << "Login name: " << users[i].getLoginName() << endl;
		cout << "Institution: " << users[i].getInstitution() << endl;
		cout << "Date of last quota payment: " << users[i].getDateString() << endl;
		if(users[i].getStatus()=='c')
					cout << users[i].getLoginName() << " is a contributer" << endl;
		if(users[i].getStatus()=='s')
					cout << users[i].getLoginName() << " is a subscriber" << endl;
		if(users[i].getStatus()=='i')
					cout << users[i].getLoginName() << " is inactive" << endl;
		cout << users[i].getLoginName() << " has sent " << users[i].getSent() << " messages and received " << users[i].getReceived() << endl;
		//print all areas of the user
		for (unsigned int j = 0; j < users[i].getVectorAreasString().size();j++) {
			cout << "Area" << j + 1 << " " << users[i].getVectorAreasString()[j]<< endl;
		}
		cout << endl;
	}
}

void APIC::printAreasFull() {
	cout << "---------------------------AREAS---------------------------" << endl;
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (i == 0)//in first element we would get error because of areas[i-1]
			cout << areas[i].getAreaName() << " - " << areas[i].getAreaNameSigla() << endl;
		else if (areas[i].getAreaName() != areas[i - 1].getAreaName())
			cout << areas[i].getAreaName() << " - " << areas[i].getAreaNameSigla() << endl;
	}
}

void APIC::printAreasSiglas() {
	vector<string> singleAreas;
	cout << "-------AREAS-------" << endl;
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (i == 0)//in first element we would get error because of areas[i-1]
			singleAreas.push_back(areas[i].getAreaNameSigla());
		else if (areas[i].getAreaNameSigla() != areas[i - 1].getAreaNameSigla())
			singleAreas.push_back(areas[i].getAreaNameSigla());
	}
	//print areas in 5 columns and 5 lines
	for (unsigned int i = 0; i < singleAreas.size(); i += 5) {
		cout << singleAreas[i] << " " << singleAreas[i + 1] << " " << singleAreas[i + 2] << " " << singleAreas[i + 3] << " " << singleAreas[i + 4] << endl;
	}
}

void APIC::printSubArea(string area) {
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (areas[i].getAreaNameSigla() == area) {
			cout << areas[i].getSubAreaName() << " - "<< areas[i].getSubAreaNameSigla() << endl;
		}
	}
}

void APIC::printAreasAndSub(){
	cout << endl << "----------All areas and sub areas----------" << endl;
	for(unsigned int i =0;i<areas.size();i++){
		cout << i+1 << " Subarea: " << areas[i].getSubAreaName() << " --------> Subarea Acronym: " << areas[i].getAreaNameSigla() << "-" << areas[i].getSubAreaNameSigla() << endl;
	}
}

void APIC::printSubAreasUser() {
	string area;
	bool find = 0;

	cout << "For which area are you looking for sub areas?" << endl;
	cout << "Type 'area?' to show  all areas available or semicolon to return" << endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');

	//if area = "area?"  prints all areas
	if (area == "area?") {
		cout << endl;
		printAreasFull();
		cout << endl << "For which area are you looking for sub areas (semicolon will return) ?" << endl;
		cout << "Your pick: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
	}

	//finds semicolon in area
	if (findSemicolon(area))
		return;
	stringToUpper(area);//turns area into capital letter

	for(unsigned int i = 0 ; i <areas.size();i++){
		if(areas[i].getAreaNameSigla()==area)
			find=1;
	}

	if (find == 1) {
		cout << endl << "---Sub Areas of " << area << "---" << endl;
		printSubArea(area);
	}
	else
		cout << endl << "Sorry! Area not found! " << endl;
}

void APIC::printEventsC() {
	for (unsigned int i = 0; i < eventsC.size(); i++) {
		cout << endl;

		cout << "Event " << i + 1 << " created by "
				<< eventsC[i].getUserCreated().getLoginName() << endl;
		cout << "Title: " << eventsC[i].getTitle() << endl;
		cout << "Will take place at " << eventsC[i].getLocal() << " on "
				<< eventsC[i].getDate().getDay() << "/"
				<< eventsC[i].getDate().getMonth() << "/"
				<< eventsC[i].getDate().getYear() << endl;
		cout << "We estimate " << eventsC[i].getNumberPeople()
				<< " people will show " << endl;
		if (eventsC[i].getSupport() == 0) {
			cout << "This event needs more people promoting it to get support "
					<< endl;
		} else if (eventsC[i].getSupport() == 1
				&& eventsC[i].getNumberPeople()<30) {
			cout
					<< "This event can not get support. Conferences need to expect 30 people to get support "
					<< endl;
		} else if (eventsC[i].getSupport() == 1
				&& eventsC[i].getNumberPeople() >= 30) {
			cout << "This event is getting support " << endl;
		}
	}
}

void APIC::printEventsSS() {
	for (unsigned int i = 0; i < eventsSS.size(); i++) {
		cout << endl;
		cout << "Event " << i + 1 << " created by "
				<< eventsSS[i].getUserCreated().getLoginName() << endl;
		cout << "Title: " << eventsSS[i].getTitle() << endl;
		cout << "Will take place at " << eventsSS[i].getLocal() << " on "
				<< eventsSS[i].getDate().getDay() << "/"
				<< eventsSS[i].getDate().getMonth() << "/"
				<< eventsSS[i].getDate().getYear() << endl;
		cout << "The formers will be: ";
		for (unsigned int j = 0; j < eventsSS[i].getFormers().size(); j++) {
			cout << eventsSS[i].getFormers()[j].getLoginName() << " ";
		}
		cout << endl;
		if (eventsSS[i].getSupport() == 0) {
			cout << "This event needs more people promoting it to get support " << endl;
		}
		else if (eventsSS[i].getSupport() == 1
						&& eventsSS[i].getFormers().size()<3){
			cout << "This event can not get support. Only summer schools with at least 3 formers get support " << endl;
		}
		else if (eventsSS[i].getSupport() == 1
				&& eventsSS[i].getFormers().size()>=3) {
			cout << "This event is getting support " << endl;
		}
	}
}

void APIC::printEvents(){
	cout << "----Conferences----" << endl;
	printEventsC();
	cout << endl << "----Summer Schools----" << endl;
	printEventsSS();
}

void APIC::printMessage(User receiver) {
	bool find = 0;

	//for all messages, find user in received vector
	for (unsigned int i = 0; i < messages.size(); i++) {
		for (unsigned int j = 0; j < messages[i].getUsersReceived().size();j++) {
			if (messages[i].getUsersReceived()[j].getLoginName()== receiver.getLoginName())
				find = 1;
		}
	}

	if (find == 0) {
		cout << endl << "Sorry! You do not have any messages yet! " << endl;
	} else {
		cout << endl << "Your messages:" << endl;
		for (unsigned int i = 0; i<messages.size(); i++) {
			for (unsigned int j = 0; j<messages[i].getUsersReceived().size();j++) {
				if (messages[i].getUsersReceived()[j].getLoginName() == receiver.getLoginName()) {
					cout << "Sent by: " << messages[i].getUserSent().getLoginName()
							<< " on " << messages[i].getDate().getDay() << "/"
							<< messages[i].getDate().getMonth() << "/"
							<< messages[i].getDate().getYear() << endl;
					cout << "Message: " << messages[i].getMessage() << endl << endl;
				}
			}
		}
	}
}

/***************************************************************
************************SEARCH FUNCTIONS************************
***************************************************************/
void APIC::searchUser() {
	string user;
	bool find = 0;
	cout << endl << "Please, insert the login name of the user you are trying to find: " << endl;
	cout << "Your pick: ";
	cin >> user;
	cin.clear();
	cin.ignore(10000, '\n');

	//finds user in users vector
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == user) {
			find = 1;
			cout << endl << "User found! " << endl;
			cout << "Login name: " << users[i].getLoginName() << endl;
			cout << "Institution: " << users[i].getInstitution() << endl;
			cout << "Date of last quota payment: " << users[i].getDateString() << endl;
			if (users[i].getStatus() == 'c')
				cout << users[i].getLoginName() << " is a contributer" << endl;
			if (users[i].getStatus() == 's')
				cout << users[i].getLoginName() << " is a subscriber" << endl;
			if (users[i].getStatus() == 'i')
				cout << users[i].getLoginName() << " is inactive" << endl;
			cout << users[i].getLoginName() << " has sent " << users[i].getSent() << " messages and received " << users[i].getReceived() << endl;
			//print all areas of the user
			for (unsigned int j = 0; j < users[i].getVectorAreasString().size();j++) {
				cout << "Area" << j + 1 << " " << users[i].getVectorAreasString()[j] << endl;
			}
		}
	}

	if(find==0){
		cout << endl << "User not found! " << endl;
	}
}

void APIC::searchEventByArea() {
	bool find = 0, find2 = 0;
	string area;
	cout << "Please insert the acronym of the area you are looking for: " << endl;
	cout << "Insert 'area?' to print all areas or semicolon to return" << endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');
	//if area has ; returns
	if (findSemicolon(area)) {
		return;
	}
	if (area == "area?") {//if area == "area?" prints all areas
		cout << endl;
		printAreasFull();
		cout << endl << "Please insert the acronym of the area you are looking for (insert semicolon to return): "<< endl;
		cout << "Your pick: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
		if (findSemicolon(area)) {
			return;
		}
	}
	stringToUpper(area);//turns area into capital letter

	//prints all conferences in selected area
	for (unsigned int i = 0; i < eventsC.size(); i++) {
		if (eventsC[i].getArea() == area)
			find = 1;
	}

	//prints all summer schools in selected area
	for (unsigned int i = 0; i < eventsSS.size(); i++) {
		if (eventsSS[i].getArea() == area)
			find2 = 1;
	}

	if (find == 0)
		cout << endl << "There are no conferences in that area!" << endl;
	else {
		cout << endl << "Conferences in that area: " << endl;
		for (unsigned int i = 0; i < eventsC.size(); i++) {
			if (eventsC[i].getArea() == area) {
				cout << "Event created by "
						<< eventsC[i].getUserCreated().getLoginName() << endl;
				cout << "Title: " << eventsC[i].getTitle() << endl;
				cout << "Will take place at " << eventsC[i].getLocal() << " on "
						<< eventsC[i].getDate().getDay() << "/"
						<< eventsC[i].getDate().getMonth() << "/"
						<< eventsC[i].getDate().getYear() << endl;
				cout << "We estimate " << eventsC[i].getNumberPeople()
						<< " people will show " << endl;
			}
		}
	}

	if (find2 == 0)
		cout << endl << "There are no summer schools in that area! " << endl;
	else {
		cout << endl <<"Summer schools in that area: " << endl;
		for (unsigned int i = 0; i < eventsC.size(); i++) {
			if (eventsC[i].getArea() == area) {
				cout << "Event created by "
						<< eventsSS[i].getUserCreated().getLoginName() << endl;
				cout << "Title: " << eventsSS[i].getTitle() << endl;
				cout << "Will take place at " << eventsSS[i].getLocal()
						<< " on " << eventsSS[i].getDate().getDay() << "/"
						<< eventsSS[i].getDate().getMonth() << "/"
						<< eventsSS[i].getDate().getYear() << endl;
				//prints all formers
				cout << "The formers will be: ";
				for (unsigned int j = 0; j < eventsSS[i].getFormers().size();
						j++) {
					cout << eventsSS[i].getFormers()[j].getLoginName() << " ";
				}
				cout << endl;
			}
		}

	}
}

void APIC::searchUserByArea() {
	string area;
	vector<string> usersVector;
	cout << endl << "Please insert the acronym of the area you are looking for: " << endl;
	cout << "Insert 'area?' to print all areas or semicolon to return" << endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');

	//if area has semicolon it returns back
	if (findSemicolon(area)) {
		return;
	}

	if (area == "area?") {//if area == "area?" prints areas
		printAreasFull();
		cout << endl << "Please insert the acronym of the area you are looking for (insert semicolon to return): " << endl;
		cout << "Your pick: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');

		//if area has semicolon it returns back
		if (findSemicolon(area)) {
			return;
		}

		stringToUpper(area);
	}

	stringToUpper(area);

	//for all users looks if area is in user areas vector. If it is inserts it in usersVector
	for (unsigned int i = 0; i < users.size(); i++) {
		for (unsigned int j = 0; j < users[i].getVectorAreas().size(); j++) {
			if (users[i].getVectorAreas()[j].getAreaNameSigla() == area)
				usersVector.push_back(users[i].getLoginName());
		}
	}

	//this lefts in the vector only the different elements
	auto last = unique(usersVector.begin(), usersVector.end());
	usersVector.erase(last, usersVector.end());

	if(usersVector.size()==0){
		cout << endl << "Sorry! Did not find any user with " << area << " in areas" << endl;
	}
	else {
		cout << endl << "Users with " << area << " in areas:" << endl;
		//prints what is left in vector
		for (unsigned int i = 0; i < usersVector.size(); i++) {
			cout << i+1 << ": " << usersVector[i] << endl;
		}
	}
}

void APIC::searchUserBySubArea() {
	string area;
	vector<string> usersVector;
	cout << "Please insert the acronym of the area and sub area you want to search in the format: 'XXX-XXX':" << endl;
	cout << "Insert 'area?' to print all areas and subareas or semicolon to return" << endl;
	cout << "Your area and sub area: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');

//try to find ";" in username
	if (findSemicolon(area))
		return;

	if(area=="area?"){
		printAreasAndSub();
		cout << endl << "Please insert the acronym of the area and sub area you want to search in the format: 'XXX-XXX' (semicolon will return) :" << endl;
		cout << "Your area and sub area: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
	}

	stringToUpper(area);

	//for all users try to find the area in the user areas vector. if finds inserts user in usersVector
	for (unsigned int i = 0; i < users.size(); i++) {
		for (unsigned int j=0; j<users[i].getVectorAreasString().size();j++) {
			if (users[i].getVectorAreasString()[j] == area)
				usersVector.push_back(users[i].getLoginName());
		}
	}

	//erases different elements in the vector
	auto last = unique(usersVector.begin(), usersVector.end());
	usersVector.erase(last, usersVector.end());

	if(usersVector.size()==0){
		cout << endl << "Sorry! Did not find any user with " << area << " in areas" << endl;
	}
	else {
		cout << endl << "Users with " << area << " in areas:" << endl;
		//prints what is left in vector
		for (unsigned int i = 0; i < usersVector.size(); i++) {
			cout << i+1 << ": " << usersVector[i] << endl;
		}
	}
}
/************************************************************
**********************CHECK FUNCTIONS************************
************************************************************/
bool APIC::checkArea(string area) {
	//if area is in areas vector returns true else returns false
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (area == areas[i].getAreaNameSigla())
			return true;
	}
	return false;
}

bool APIC::checkSubArea(string subArea) {
	//if subarea is in subareas vector returns true else returns false
	for (unsigned int i=0; i<areas.size(); i++) {
		if (subArea == areas[i].getSubAreaNameSigla())
			return true;
	}
	return false;
}

bool APIC::findSemicolon(string stringToSearch) {
	//if it finds semicolon in string returns true else returns false
	basic_string<char>::size_type index1, index2;
	static const basic_string<char>::size_type npos = -1;
	index1 = stringToSearch.find(';');
	index2 = stringToSearch.find(',');

	if (index1 != npos || index2 != npos) {
		cout << "You returned back! " << endl << endl;
		return true;
	} else
		return false;
}

bool APIC::checkStatusC(APIC apic){
	for(unsigned int i=0;i<users.size();i++){
		if(users[i].getLoginName()==apic.getUserLogged().getLoginName()){
			if(users[i].getStatus()=='c')
				return true;
			else
				return false;
		}
	}
	return false;
}

bool APIC::checkStatusI(APIC apic){
	for(unsigned int i=0;i<users.size();i++){
		if(users[i].getLoginName()==apic.getUserLogged().getLoginName()){
			if(users[i].getStatus()=='i')
				return true;
			else
				return false;
		}
	}
	return false;
}

/************************************************************
 **********************CREATE FUNCTIONS**********************
 ************************************************************/
void APIC::createEvent(APIC apic) {
	int pick;
	do {//only exits when input is valid
		cout << endl << "What type of event do you want to create? " << endl;
		cout << "1: Conference" << endl;
		cout << "2: Summer School" << endl;
		cout << "0: Exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case 1:
			createConference(apic);
			break;
		case 2:
			createSummerSchool(apic);
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong pick! Please pick again" << endl;
			break;
		}
	} while (pick <= 0 || pick > 2);
}

void APIC::createSummerSchool(APIC apic) {
	int pick, ok = 1, error = 0;
	bool exit = 0;
	string local, dateString, newFormer, title, area;
	vector<User> formers;
	vector<User> promoters;

	do {//only exits when area is added
		cout << endl << "Enter the scientific area of which your event is about: " << endl;
		cout << "Enter 'area?' to display all areas. Enter semicolon or comma will return back " << endl;
		cout << "Your pick: " << endl;
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');

		//try to find ";" in area
		if (findSemicolon(area))
			return;

		if (area == "area?") {//if area == "area?" it prints all areas
			printAreasFull();
			cout << endl << "Please insert the acronym of the area want to add: " << endl;
			cout << "Insert semicolon to return" << endl;
			cout << "Your pick: ";
			cin >> area;
			cin.clear();
			cin.ignore(10000, '\n');
			if (findSemicolon(area)) {
				return;
			}
		}
		//turns area to capital letters
		stringToUpper(area);
		//checks if area exists
		if (checkArea(area)) {
			cout << "Area found and added! " << endl;
			exit = 1;
		} else
			cout << "Area not found! Please try again! " << endl;
	} while (exit == 0);

	cout << "Where will the event take place? (semicolon will return back) " << endl;
	cout << "Local: ";
	getline(cin,local);
	//try to find ";" in local
	if (findSemicolon(local))
		return;

	do {//exists only when date is a future date
		cout << "In which date will the event take place? (format: 'dd/mm/yyyy' Semicolon will return back) " << endl;
		cout << "Date: ";
		cin >> dateString;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in dateString
		if (findSemicolon(dateString))
			return;

		Date date(dateString);
		if (!date.isFuture()) { //checks if date is a future date
			cout << "ERROR! You need to enter a future date!" << endl;
			error = 1;
		} else
			error = 0;
	} while (error == 1);

	Date date(dateString);

	cout << "Please insert a title for the event: (Semicolon will return back) " << endl;
	cout << "Title: ";
	getline(cin,title);

	//try to find ";" in title
	if (findSemicolon(title))
		return;

	cout << endl;
	printUsers();
	cout << endl;
	do { //exits only when user does not want to add more formers
		ok = 1;
		cout << "Insert the name of the user you want to add as former: (Semicolon will return back) " << endl;
		cout << "Former: ";
		cin >> newFormer;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in newFormer
		if (findSemicolon(newFormer))
			return;

		//finds former in users vector
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == newFormer) {
				formers.push_back(users[i]);
				ok = 0; //to mark that former has been found
			}
		}
		if (ok == 1)
			cout << "Sorry. Could not find your user. " << endl;
		cout << "Do you want to add more formers? (1 for yes or 2 for no)" << endl;
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	} while (pick == 1);
	if (ok == 0) //ok==0 means former has been found
		cout << "Success! Event created! " << endl;

	EventSummerSchool newSummerSchool(apic.getUserLogged(), local, title, date, area, 0, formers, promoters);
	insertEventSS(newSummerSchool);

	//writes the new summer school in the file
	ofstream eventsSSFile;
	eventsSSFile.open("eventsSS.txt", ofstream::app);
	eventsSSFile << apic.getUserLogged().getLoginName() << ";" << local << ";" << title << ";" << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << ";" << area << ";" << 0 << ";";

	//writes all formers of each user in the file
	for (unsigned int i = 0; i < formers.size(); i++) {
		//if it is the last element end with ';'
		if (i + 1 == formers.size())
			eventsSSFile << formers[i].getLoginName() << "," << endl;
		//other elements end with ';'
		else
			eventsSSFile << formers[i].getLoginName() << ";";
	}

	//closes file
	eventsSSFile.close();
}

void APIC::createConference(APIC apic) {
	unsigned int numberPeople, error = 0;
	bool exit = 0;
	string local, dateString, newFormer, title, area;
	vector<User> promoters;

	do {//exits only when area is found
		cout << endl << "Enter the scientific area of which your event is about: " << endl;
		cout << "Enter 'area?' to display all areas. Enter semicolon or comma will return back " << endl;
		cout << "Your pick: " << endl;
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');

		//try to find ";" in area
		if (findSemicolon(area))
			return;

		//if area == "area?" prints areas complete info
		if (area == "area?") {
			//prints all areas
			printAreasFull();
			cout << endl << "Please insert the acronym of the area want to add: " << endl;
			cout << "Insert semicolon will return" << endl;
			cout << "Your pick: ";
			cin >> area;
			cin.clear();
			cin.ignore(10000, '\n');

			//finds ";" in area
			if (findSemicolon(area))
				return;

		}
		//turns area into capital letters
		stringToUpper(area);
		//if area exists turns exit into true
		if (checkArea(area)) {
			cout << "Area found and added! " << endl;
			exit = 1;
		} else
			cout << "Area not found! Please try again! " << endl;
	} while (exit == 0);//exists if area was found

	cout << "Where will the event take place? (Semicolon will return back)"<< endl;
	cout << "Local: ";
	getline(cin,local);

	//try to find ";" in local
	if (findSemicolon(local))
		return;

	do {//exits if area is a future date
		cout << "In which date will the event take place? (format: 'dd/mm/yyyy' Semicolon will return back) " << endl;
		cout << "Date: ";
		cin >> dateString;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in dateString
		if (findSemicolon(dateString))
			return;

		Date date(dateString);
		//checks if date is future
		if (!date.isFuture()) {
			cout << "ERROR! You need to enter a future date!" << endl;
			error = 1;
		} else
			error = 0;
	} while (error == 1);

	Date date(dateString);

	cout << "Please insert a title for the event: (Semicolon will return back) " << endl;
	cout << "Title: ";
	getline(cin,title);

	//try to find ";" in title
	if (findSemicolon(title))
		return;

	cout << "Please insert the number of people you think that will show for this event: " << endl;
	cout << "Number of people: ";
	cin >> numberPeople;
	if (cin.fail())
		cout << "ERROR! Wrong input! " << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Success! Event created! " << endl;
	cout << "You can now message other users to promote your event!" << endl;

	EventConference newConference(apic.getUserLogged(), local, title, date, area, 0, numberPeople,promoters);
	insertEventC(newConference);

	//writes conference file
	ofstream eventsCFile;
	eventsCFile.open("eventsC.txt", ofstream::app);
	eventsCFile << apic.getUserLogged().getLoginName() << ";" << local << ";"
			<< title << ";" << date.getDay() << "/" << date.getMonth() << "/"
			<< date.getYear() << ";" << area << ";0;" << numberPeople << ";"
			<< endl;

	eventsCFile.close();
}

void APIC::createMessage(APIC apic) {
	bool exit = 0, skip = 0, skip2=0, find = 0, find2=0;
	int pick,pick2,pick3;
	string areaString, msg, newUserString;
	vector<string> areasS;
	vector<User> receivers;

	do {//leaves when pick=1 or pick=2
		cout << endl << "How do you want to choose who gets the message? " << endl;
		cout << "1: Choose by areas" << endl;
		cout << "2: Choose by users" << endl;
		cout << "Your pick: ";
		cin >> pick2;
		cin.clear();
		cin.ignore(10000, '\n');
	} while (pick2 != 1 && pick2 != 2);

	//chose by area
	if(pick2==1){
		do { //exits if user do not want to add more areas
			cout << endl << "Please insert the area that you want to share this message with (semicolon will return): " << endl;
			cout << "Enter 'area?' to display all areas or enter 'all' will share this message with all areas " << endl;
			cout << "Your pick: ";
			cin >> areaString;
			cin.clear();
			cin.ignore(10000, '\n');
			//try to find ";" in area
			if (findSemicolon(areaString))
				return;

			//if area == "area?" prints areas complete info
			if (areaString == "area?") {
				//prints all areas
				printAreasFull();
				cout << endl << "Please insert the acronym of the area want to add: (semicolon will return) " << endl;
				cout << "Your pick: ";
				cin >> areaString;
				cin.clear();
				cin.ignore(10000, '\n');

				//find ";" in areaString
				if (findSemicolon(areaString))
					return;
			}

			//if areaString is "all" all areas will be selected
			if (areaString == "all") {
				cout << "This message will be sent to every area! " << endl;
				skip = 1;
				exit = 1;
			}

			if (skip == 0) { //skip == 0 when all areas were printed
				stringToUpper(areaString);
				if (checkArea(areaString)) {
					areasS.push_back(areaString);
					cout << "Area found and added! " << endl;
					cout << "Do you want to add another area?" << endl;
					cout << "1: Yes" << endl << "2: No" << endl;
					cout << "Your pick: ";
					cin >> pick;
					cin.clear();
					cin.ignore(10000, '\n');
					if (pick == 2)
						exit = 1;
					else if (pick != 1)
						cout << "Wrong input! Will assume you don't want to add more areas! " << endl;
				} else
					cout << "Area not found! Please try again! " << endl;
			}
		} while (exit == 0);

		//if areaString == "all" the message is sent to everyone
		if (areaString == "all") {
			for (unsigned int i = 0; i < users.size(); i++) {
				if (users[i].getStatus() == 'c' || users[i].getStatus() == 's')
					receivers.push_back(users[i]);
			}
		} else {
			//try to find every area in the users areas vector. if the user has that area it is inserted to receivers vector
			for (unsigned int i = 0; i < areasS.size(); i++) {
				for (unsigned int j = 0; j < users.size(); j++) {
					find = 0;
					for (unsigned int k = 0;
							k < users[j].getVectorAreas().size(); k++) {
						if (areasS[i]== users[j].getVectorAreas()[k].getAreaNameSigla()) {
							for (unsigned int l = 0; l < receivers.size();l++) {
								if (receivers[l].getLoginName() == users[j].getLoginName())
									find = 1;
							}
							if (find == 0)
								receivers.push_back(users[j]);
						}
					}
				}
			}
		}
	}

	//choose by user
	if (pick2 == 2) {
		do { //leaves when user does not want to add more receivers
			do { //leaves when user is found
				find2 = 0;
				cout << endl << "Insert the name of the user you want to send this message (semicolon will return back): " << endl;
				cout << "Type 'users?' to print all usernames or type 'all' to send message to all users" << endl;
				cout << "User: ";
				cin >> newUserString;
				cin.clear();
				cin.ignore(10000, '\n');
				if(findSemicolon(newUserString))
					return;

				if(newUserString=="users?"){
					printUsers();
					cout << endl << "Insert the name of the user you want to send this message (semicolon will return back): " << endl;
					cout << "Type 'all' to send message to all users" << endl;
					cout << "User: ";
					cin >> newUserString;
					cin.clear();
					cin.ignore(10000, '\n');
					if(findSemicolon(newUserString))
						return;
				}

				if(newUserString=="all"){
					skip2=1;
					find2=1;
					pick3=0;
					for(unsigned int i=0;i<users.size();i++){
						receivers.push_back(users[i]);
					}

				}

				if (skip2 == 0) {
					for (unsigned int i = 0; i < users.size(); i++) {
						if (users[i].getLoginName() == newUserString) {
							receivers.push_back(users[i]);
							find2 = 1;
						}
					}

					if (find2 == 0)
						cout << "Sorry! Could not find your user. Try again. " << endl;
					else {
						cout << endl << newUserString << " will receive your message." << endl;
						do{
						cout << "Do you want to sent the message to more users? " << endl;
						cout << "1: Yes" << endl;
						cout << "2: No" << endl;
						cout << "Pick: ";
						cin >> pick3;
						cin.clear();
						cin.ignore(10000, '\n');}while(pick3!=1 && pick3!=2);
					}
				}
			} while (find2 == 0);
		} while (pick3 == 1);
	}

	Date todayDate = getTodayDate();

	cout << endl << "Insert your message: " << endl;
	cout << "Message: ";
	getline(cin, msg);

	//increments the number of messages this user has sent
	for (unsigned int i = 0; i < users.size(); i++) {
		if (apic.getUserLogged().getLoginName() == users[i].getLoginName())
			users[i].setSent(users[i].getSent() + 1);
	}

	//increments the number of messages received for all users that will receive this message
	for (unsigned int i = 0; i < receivers.size(); i++) {
		for (unsigned int j = 0; j < users.size(); j++) {
			if (receivers[i].getLoginName() == users[j].getLoginName()) {
				users[j].setReceived(users[j].getReceived() + 1);
			}
		}
	}

	//re-writes the users file with the new sent/received
	remove("users.txt");
	ofstream usersFile;
	usersFile.open("users.txt");
	for (unsigned int i = 0; i < users.size(); i++) {
		usersFile << users[i].getLoginName() << ";" << users[i].getPassword()
				<< ";" << users[i].getInstitution() << ";"
				<< users[i].getDatePay().getDay() << "/"
				<< users[i].getDatePay().getMonth() << "/"
				<< users[i].getDatePay().getYear() << ";" << users[i].getSent()
				<< ";" << users[i].getReceived() << ";";

		//prints all areas
		for (unsigned int j = 0; j < users[i].getVectorAreasString().size();j++) {
			//if it is the last element it ends with "," and new line
			if (j + 1 == users[i].getVectorAreasString().size())
				usersFile << users[i].getVectorAreas()[j].getAreaNameSigla() << "-" << users[i].getVectorAreas()[j].getSubAreaNameSigla() << "," << endl;
			//if it is not the last element ends with ";"
			else
				usersFile << users[i].getVectorAreas()[j].getAreaNameSigla() << "-" << users[i].getVectorAreas()[j].getSubAreaNameSigla() << ";";
		}
	}

	//closes the users file
	usersFile.close();

	//creates the message and puts it in messages vector
	Message newMessage(apic.getUserLogged(), todayDate, msg, receivers);
	messages.push_back(newMessage);

	//writes to the msg.txt
	ofstream msgFile;
	msgFile.open("msg.txt", ofstream::app);
	msgFile << apic.getUserLogged().getLoginName() << ";" << todayDate.getDay() << "/" << todayDate.getMonth() << "/" << todayDate.getYear() << ";" << msg << ";";

	//writes the receivers login name
	for (unsigned int i = 0; i < receivers.size(); i++) {
		//if it is the last element it ends with ','
		if (i + 1 == receivers.size())
			msgFile << receivers[i].getLoginName() << ",";
		//if it is not the last element it ends with ";"
		else
			msgFile << receivers[i].getLoginName() << ";";
	}
	msgFile << endl;

	//closes message file
	msgFile.close();
	cout << "Message sent! " << endl;
}



/*******************************************************
*********************LOAD FUNCTIONS*********************
********************************************************/
void APIC::loadUsers() {
	fstream usersFile("users.txt");
	string line;
	stringstream ss;

	//create user per line and insert in vector
	while (usersFile.good()) {
		ss.clear();
		getline(usersFile, line, '\n');
		if (line != "") {
			ss << line;
			User newUser(ss, areas);
			insertUser(newUser);
		}
	}
}
void APIC::loadAreas() {
	fstream areasFile("areas.txt");
	string line2;
	stringstream ss2;

	//create area per line and insert in vector
	while (areasFile.good()) {
		ss2.clear();
		getline(areasFile, line2, '\n');
		if (line2 != "") {
			ss2 << line2;
			Area newArea(ss2);
			insertArea(newArea);
		}
	}
}

void APIC::loadEventsSS() {
	fstream eventsSSFile("eventsSS.txt");
	string line2;
	stringstream ss2;

	//create summer school per line and insert into vector
	while (eventsSSFile.good()) {
		ss2.clear();
		getline(eventsSSFile, line2, '\n');
		if (line2 != "") {
			ss2 << line2;
			EventSummerSchool newEventSS = readSummerSchool(ss2);
			insertEventSS(newEventSS);
		}
	}
}

void APIC::loadEventsC() {
	fstream eventsCFile("eventsC.txt");
	string line2;
	stringstream ss2;

	//create conference per line and insert into vector
	while (eventsCFile.good()) {
		ss2.clear();
		getline(eventsCFile, line2, '\n');
		if (line2 != "") {
			ss2 << line2;
			EventConference newEventC = readConference(ss2);
			insertEventC(newEventC);
		}
	}
}

void APIC::loadMessages() {
	fstream msgFile("msg.txt");
	string line2;
	stringstream ss2;

	//create message per line and insert into vector
	while (msgFile.good()) {
		ss2.clear();
		getline(msgFile, line2, '\n');
		if (line2 != "") {
			ss2 << line2;
			Message newMessage = readMessage(ss2);
			insertMessage(newMessage);
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++READ FUNCTIONS++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

EventSummerSchool APIC::readSummerSchool(stringstream & s) {
	string newUserString, newDateString, newLocal, newTitle, newArea, newSupportString, newFormersString, newPromotersString;
	int newSupport;
	User newUser;
	vector<User> newFormers;
	vector<User> newPromoters;

	//read user
	if (!getline(s, newUserString, ';'))
		cout << "Error reading login name " << endl;

	//find the user in users vector
	for (unsigned int i = 0; i<users.size(); i++) {
		if (users[i].getLoginName() == newUserString)
			newUser = users[i];
	}

	//read local
	if (!getline(s, newLocal, ';'))
		cout << "Error reading local " << endl;

	//read title
	if (!getline(s, newTitle, ';'))
		cout << "Error reading title " << endl;

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error reading date string " << endl;

	Date newDate(newDateString);

	//read area
	if (!getline(s, newArea, ';'))
		cout << "Error reading area " << endl;

	//read support status
	if (!getline(s, newSupportString, ';'))
		cout << "Error reading support " << endl;

	//converts newSupportString to int
	newSupport = stoi(newSupportString);

	//read all formers
	if (!getline(s, newFormersString, ','))
		cout << "Error reading former " << endl;

	istringstream iss(newFormersString);
	string formerLoginName;
	while (getline(iss, formerLoginName, ';')) {
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == formerLoginName) {
				newFormers.push_back(users[i]);
			}
		}
	}

	//read all promoters
	getline(s, newPromotersString, ',');

	istringstream iss2(newPromotersString);
	string promoterLoginName;
	while (getline(iss2, promoterLoginName, ';')) {
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == promoterLoginName) {
				newPromoters.push_back(users[i]);
			}
		}
	}

	EventSummerSchool newSS(newUser, newLocal, newTitle, newDate, newArea, newSupport, newFormers, newPromoters);
	return newSS;
}

EventConference APIC::readConference(stringstream & s) {
	string newUserString, newDateString, newLocal, newTitle, numberString, newArea, newSupportString, newPromotersString;
	int newNumber, newSupport;
	User newUser;
	vector<User> newPromoters;

	//read user
	if (!getline(s, newUserString, ';'))
		cout << "Error reading login name " << endl;

	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == newUserString)
			newUser = users[i];
	}

	//read local
	if (!getline(s, newLocal, ';'))
		cout << "Error reading local " << endl;

	//read title
	if (!getline(s, newTitle, ';'))
		cout << "Error reading title " << endl;

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error reading conference " << endl;

	Date newDate(newDateString);

	//read area
	if (!getline(s, newArea, ';'))
		cout << "Error reading area " << endl;

	//read support status
	if (!getline(s, newSupportString, ';'))
		cout << "Error reading support status " << endl;

	newSupport = stoi(newSupportString);

	//read people expected
	if (!getline(s, numberString, ';'))
		cout << "Error reading number of people " << endl;

	//converts numberString to int
	newNumber = stoi(numberString);

	//read all promoters
	getline(s, newPromotersString, ',');

	istringstream iss2(newPromotersString);
	string promoterLoginName;
	while (getline(iss2, promoterLoginName, ';')) {
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == promoterLoginName) {
				newPromoters.push_back(users[i]);
			}
		}
	}

	EventConference newC(newUser, newLocal, newTitle, newDate, newArea, newSupport, newNumber, newPromoters);
	return newC;
}

Message APIC::readMessage(stringstream& s) {
	string newUserString, newDateString, newReceiverString, newMessage;
	User newUser;
	vector<User> newReceivers;

	//read user
	if (!getline(s, newUserString, ';'))
		cout << "Error reading message " << endl;

	//finds the user in the vector
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == newUserString)
			newUser = users[i];
	}

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error reading date " << endl;

	Date newDate(newDateString);

	//read message
	if (!getline(s, newMessage, ';'))
		cout << "Error reading message " << endl;

	//read all receivers
	getline(s, newReceiverString, ',');

	istringstream iss(newReceiverString);
	string receiverLoginName;
	while (getline(iss, receiverLoginName, ';')) {
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == receiverLoginName)
				newReceivers.push_back(users[i]);
		}
	}

	Message newMsg(newUser, newDate, newMessage, newReceivers);
	return newMsg;
}

/***************************************************************
 *********************WRITE FUNCIONS****************************
 **************************************************************/

void APIC::writeEventsSS() {
	remove("eventsSS.txt");

	ofstream eventsSSFile;
	eventsSSFile.open("eventsSS.txt");
	for (unsigned int i = 0; i < eventsSS.size(); i++) {
		eventsSSFile << eventsSS[i].getUserCreated().getLoginName() << ";"
				<< eventsSS[i].getLocal() << ";" << eventsSS[i].getTitle()
				<< ";" << eventsSS[i].getDate().getDay() << "/"
				<< eventsSS[i].getDate().getMonth() << "/"
				<< eventsSS[i].getDate().getYear() << ";"
				<< eventsSS[i].getArea() << ";" << eventsSS[i].getSupport()
				<< ";";
		for (unsigned int j = 0; j < eventsSS[i].getFormers().size(); j++) {
			if (j + 1 == eventsSS[i].getFormers().size()) {
				eventsSSFile << eventsSS[i].getFormers()[j].getLoginName()
						<< ",";
				if (eventsSS[i].getUsersPromoted().size() == 0) {
					cout << endl;
				}
			} else {
				eventsSSFile << eventsSS[i].getFormers()[j].getLoginName()
						<< ";";
			}
		}
		for (unsigned int j = 0; j < eventsSS[i].getUsersPromoted().size();
				j++) {
			if (j + 1 == eventsSS[i].getUsersPromoted().size())
				eventsSSFile << eventsSS[i].getUsersPromoted()[j].getLoginName()
						<< "," << endl;
			else
				eventsSSFile << eventsSS[i].getUsersPromoted()[j].getLoginName()
						<< ";";
		}
	}
}

void APIC::writeEventsC() {
	remove("eventsC.txt");
	ofstream eventsCFile;
	eventsCFile.open("eventsC.txt");
	for (unsigned int i = 0; i < eventsC.size(); i++) {
		eventsCFile << eventsC[i].getUserCreated().getLoginName() << ";"
				<< eventsC[i].getLocal() << ";" << eventsC[i].getTitle() << ";"
				<< eventsC[i].getDate().getDay() << "/"
				<< eventsC[i].getDate().getMonth() << "/"
				<< eventsC[i].getDate().getYear() << ";" << eventsC[i].getArea()
				<< ";" << eventsC[i].getSupport() << ";"
				<< eventsC[i].getNumberPeople() << ";";
		if (eventsC[i].getUsersPromoted().size() == 0) {
			eventsCFile << endl;
		}
		for (unsigned int j = 0; j < eventsC[i].getUsersPromoted().size();
				j++) {
			if (j + 1 == eventsC[i].getUsersPromoted().size())
				eventsCFile << eventsC[i].getUsersPromoted()[j].getLoginName()
						<< "," << endl;
			else
				eventsCFile << eventsC[i].getUsersPromoted()[j].getLoginName()
						<< ";";
		}
	}
}

/***************************************************************
 ****************OTHER FUNCTIONS********************************
 **************************************************************/
bool APIC::login(int n, APIC apic) {
	cout << endl <<  "-----LOGGIN IN-----" << endl;
	APIC apic_ = apic;
	ifstream usersFile("users.txt");

	string username, password;
	int loginTry = n;

	//read username
	cout << "Enter username (semicolon or comma will exit): ";
	cin >> username;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in username
	if (findSemicolon(username))
		menu1(apic);

	//read password
	cout << "Enter password (semicolon or comma will exit): ";
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');

	//try to find ";" in username
	if (findSemicolon(password))
		menu1(apic);

	//search in users vector if username and password exist
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == username && users[i].getPassword() == password) {
			users[i].login();
			apic.setUserLogged(users[i]);
			cout << "Login Successful!" << endl;
			menu2(apic);
		}
	}

	//if it doesn't exist repeats and have 1 less try
	cout << "ERROR: Wrong username or password! " << endl;
	cout << "You have " << loginTry << " tries left!" << endl;
	loginTry--;
	if (loginTry > 0) {
		apic.login(loginTry, apic);
	} else {
		cout << "ERROR: You failed to login to many times!" << endl << endl;
		exit(EXIT_FAILURE);
	}

	return false;
}

bool APIC::regist(APIC apic) {
	cout << endl << "----REGISTING NEW ACCOUNT----" << endl;
	string username, password, institution, areaCompleteString;
	string date = "1/1/1900";
	vector<string> areaVector;
	int pick, pick2;
	string area, subarea;
	bool exit = false, exit2 = false;
	stringstream ss;
	stringstream areaComplete;

	cout << "Select your username (semicolon or comma will exit): "<< endl;
	cout << "Username: ";
	cin >> username;
	cin.clear();
	cin.ignore(10000, '\n');

//try to find ";" in username
	if (findSemicolon(username))
		menu1(apic);

//search if username is taken
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == username) {
			cout << "ERRO! Username is taken!" << endl << endl;
			return false;
		}
	}

	cout << endl << "Select your password (semicolon or comma will exit): "<< endl;
	cout << "Password: ";
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in password
	if (findSemicolon(password))
		menu1(apic);

	cout << endl << "Select your institution (semicolon or comma will exit): " << endl;
	cout << "Institution: ";
	cin >> institution;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in institution
	if (findSemicolon(institution))
		menu1(apic);

	do {//exit only if find area and subarea
		do {//repeat until get good input
			cout << endl << "How do you want to visualize the areas of interest?"<< endl;
			cout << "1: The full name" << endl;
			cout << "2: Just acronyms" << endl;
			cout << "3: I do not want to visualize it" << endl;
			cout << "Your pick: ";
			cin >> pick2;
			if (cin.fail())
				cout << "ERROR! Wrong input! " << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << endl;

			switch (pick2) {
			case 1:
				printAreasFull();
				exit = true;
				break;
			case 2:
				printAreasSiglas();
				exit = true;
				break;
			case 3:
				exit = true;
				break;
			default:
				cout << "Wrong input!" << endl << endl;
				break;
			}
		} while (exit == false);

		do {//repeat until user don't want to add more areas
			cout << endl << "Please choose the area you want to add (Semicolon will return back): " << endl;
			cout << "Your area: ";
			cin >> area;
			cin.clear();
			cin.ignore(10000, '\n');
			if (findSemicolon(area))
				menu1(apic);
			stringToUpper(area);

			if (checkArea(area)) {
				cout << endl << "Now please pick a sub area (Semicolon will return back): " << endl;
				printSubArea(area);
				cout << endl;
				cout << "Your sub area: ";
				cin >> subarea;
				cin.clear();
				cin.ignore(10000, '\n');
				if (findSemicolon(subarea))
					menu1(apic);

				stringToUpper(subarea);
				if (checkSubArea(subarea)) {
					cout << "Your area was added with success! " << endl;
					exit = true;
					areaComplete.clear();
					areaComplete << area << "-" << subarea;
					areaComplete >> areaCompleteString;
					areaVector.push_back(areaCompleteString);
					cout << "Do you want to add another area (1 for yes, anything else for no) ?" << endl;
					cout << "Your pick: ";
					cin >> pick;
					cin.clear();
					cin.ignore(10000, '\n');
				} else {
					cout << "Could not find your sub area ! " << endl;
					pick = 1;
				}
			} else {
				cout << "Could not find your area ! " << endl;
				pick = 1;
			}

		} while (pick == 1);
		if (pick != 1)
			exit2 = true;
	} while (exit2 == false);

	ss << username << ";";
	ss << password << ";";
	ss << institution << ";";
	ss << date << ";0;0;";

//file with users names for output
	ofstream usersFile;
	usersFile.open("users.txt", ofstream::app);
	usersFile << username << ";" << password << ";" << institution << ";" << date << ";0;0;";

	//write all areas
	for (unsigned int i = 0; i < areaVector.size(); i++) {
		//if last area write "," if not write ";"
		if (i + 1 == areaVector.size()) {
			usersFile << areaVector[i] << "," << endl;
			ss << areaVector[i] << "," << endl;
		} else {
			usersFile << areaVector[i] << ";";
			ss << areaVector[i] << ";";
		}
	}

	//create user and insert to vector
	User newUser(ss, areas);
	users.push_back(newUser);

	usersFile.close();
	return true;
}


void APIC::payQuota(APIC apic) {
	Date todayDate = getTodayDate();
	//changes the status to 'c' in the user logged in
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == apic.getUserLogged().getLoginName()) {
			users[i].setDatePay(todayDate);
			users[i].setStatus('c');
		}
	}

	//re-writes user file with updated info
	remove("users.txt");
	ofstream usersFile;
	usersFile.open("users.txt");
	for (unsigned int i = 0; i < users.size(); i++) {
		usersFile << users[i].getLoginName() << ";" << users[i].getPassword()
				<< ";" << users[i].getInstitution() << ";"
				<< users[i].getDatePay().getDay() << "/"
				<< users[i].getDatePay().getMonth() << "/"
				<< users[i].getDatePay().getYear() << ";0;0;";
		//prints all areas of the user. if it is the last element prints "," else prints ";"
		for (unsigned int j = 0; j < users[i].getVectorAreasString().size();
				j++) {
			if (j + 1 == users[i].getVectorAreasString().size())
				usersFile << users[i].getVectorAreas()[j].getAreaNameSigla() << "-" << users[i].getVectorAreas()[j].getSubAreaNameSigla() << "," << endl;
			else
				usersFile << users[i].getVectorAreas()[j].getAreaNameSigla() << "-" << users[i].getVectorAreas()[j].getSubAreaNameSigla() << ";";
		}
	}

	cout << endl<< "Thank you!" << endl;
	cout << "Your quota has been paid. You have now full access! " << endl;
}

void APIC::stringToUpper(string &s) {
	//takes a string and turns it into capital letters
	for (unsigned int l = 0; l < s.length(); l++) {
		s[l] = toupper(s[l]);
	}
}

void APIC::promoteEvent(APIC apic) {

	unsigned int pick, pick2;

	do {
		cout << endl << "What type of event do you want to promote? " << endl;
		cout << "1: Conference" << endl;
		cout << "2: Summer School" << endl;
		cout << "0: Exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case 1:
			printEventsC();
			do {
				cout << endl << "Insert the number of the event you want to promote:" << endl;
				cout << "Your pick: ";
				cin >> pick2;
				cin.clear();
				cin.ignore(10000, '\n');
			} while (pick2 < 1 || pick2 > eventsC.size());
			for (unsigned int i = 0; i < eventsC.size(); i++) {
				if (i + 1 == pick2) {
					eventsC[i].insertPromoter(apic.getUserLogged());
					updateEventSupportC(eventsC[i]);
					writeEventsC();
				}
			}
			break;
		case 2:
			printEventsSS();
			do {
				cout << endl << "Insert the number of the event you want to promote:" << endl;
				cout << "Your pick: ";
				cin >> pick2;
				cin.clear();
				cin.ignore(10000, '\n');
			} while (pick2 < 1 || pick2 > (eventsSS.size()));
			for (unsigned int i = 0; i < eventsSS.size(); i++) {
				if (i + 1 == pick2) {
					eventsSS[i].insertPromoter(apic.getUserLogged());
					updateEventSupportSS(eventsSS[i]);
					writeEventsSS();
				}
			}
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong pick! Please pick again" << endl;
			break;
		}
	} while (pick <= 0 || pick > 2);
}


void APIC::updateEventSupportC(EventConference eventC) {
	//updates to 1 if more than 50 people show
	if (eventC.getUsersPromoted().size() >= 2 && eventC.getSupport() == 0 && eventC.getNumberPeople()>=50) {
		for (unsigned int i = 0; i < eventsC.size(); i++) {
			if (eventsC[i].getTitle() == eventC.getTitle()) {
				eventsC[i].setSupport(1);
			}
		}
	}
}

void APIC::updateEventSupportSS(EventSummerSchool eventSS) {
	//updates to 1 if more than 2 formers
	if (eventSS.getUsersPromoted().size() >= 2 && eventSS.getSupport() == 0 && eventSS.getFormers().size()>2) {
		for (unsigned int i = 0; i < eventsSS.size(); i++) {
			if (eventsSS[i].getTitle() == eventSS.getTitle()) {
				eventsSS[i].setSupport(1);
			}
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++MENUS++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void APIC::menu1(APIC apic) {

	char pick;
	do {
		cout << "---Welcome!---" << endl << endl;
		cout << "Please press:" << endl;
		cout << "1: To login" << endl;
		cout << "2: To register" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case '1':
			//login
			apic.login(3, apic);
			break;
		case '2': {
			//register
			bool reg = apic.regist(apic);
			if (reg) {
				cout << endl << "Success! Account created!" << endl;
				cout << "Pay your annual quota for full access!" << endl << endl;
			}
			pick = 3;
			break;
		}
		case '0':
			//closes program
			cout << "See you soon!" << endl;
			exit(EXIT_FAILURE);
		default:
			cout << "Wrong pick! Please pick again" << endl << endl;
			break;
		}
	} while (true);
}

void APIC::menu2(APIC apic) {
	char pick;
	do {//exits when input is valid
		cout << endl << "------Welcome " << apic.getUserLogged().getLoginName()<< "------" << endl;
		cout << "Please choose what you want to do next: " << endl;
		cout << "1: Go to search and print menu" << endl;
		cout << "2: Go to the message menu" << endl;
		cout << "3: Go to events menu" << endl;
		cout << "4: Pay my quota " << endl;
		cout << "5: To Log Out" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case '1': {
			menuSearch(apic);
			break;
		}
		case '2': {
			menuMessages(apic);
			break;
		}
		case '3': {
			menuEvents(apic);
			break;
		}

		case '4': {
			payQuota(apic);
			break;
		}
		case '5': {
			cout << endl;
			//logs out the user
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case '0': {
			cout << "See you soon!" << endl;
			//closes program
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}

void APIC::menuSearch(APIC apic) {
	char pick;

	do {//exits when input is valid
		cout << endl << "----Search and Print Menu----" << endl;
		cout << "Please choose what you want to do next: " << endl;
		cout << "1: See all other users names" << endl;
		cout << "2: See every information of all users" << endl;
		cout << "3: Search for an user by its name" << endl;
		cout << "4: Search for all users in an area" << endl;
		cout << "5: Search for all users in an subarea" << endl;
		cout << "6: Search for an event" << endl;
		cout << "7: Print all areas of interest with complete name" << endl;
		cout << "8: Print all areas of interest, but just acronyms" << endl;
		cout << "9: Look for the subareas of an area" << endl;
		cout << "e: Print complete information for the events " << endl;
		cout << "x: Go to previous menu" << endl;
		cout << "z: To Log Out" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case '1': {
			printUsers();
			break;
		}
		case '2': {
			printUsersComplete();
			break;
		}
		case '3': {
			searchUser();
			break;
		}
		case '4': {
			cout << endl;
			searchUserByArea();
			break;
		}
		case '5': {
			cout << endl;
			searchUserBySubArea();
			break;
		}
		case '6': {
			cout << endl;
			searchEventByArea();
			break;
		}
		case '7': {
			cout << endl;
			printAreasFull();
			break;
		}
		case '8': {
			cout << endl;
			printAreasSiglas();
			break;
		}
		case '9': {
			cout << endl;
			printSubAreasUser();
			break;
		}
		case 'e': {
			cout << endl;
			printEvents();
			break;
		}
		case 'x': {
			//returns to previous menu
			return;
			break;
		}
		case 'z': {
			cout << endl;
			//logs out the user
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case '0': {
			cout << "See you soon!" << endl;
			//leaves program
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}

void APIC::menuEvents(APIC apic) {
	char pick;

	do {//exits when input is valid
		cout << endl << "----Events Menu----" << endl;
		cout << "Please choose what you want to do next: " << endl;
		cout << "1: Create event" << endl;
		cout << "2: Promote event" << endl;
		cout << "3: Search for an event" << endl;
		cout << "4: Go to previous menu" << endl;
		cout << "5: To Log Out" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case '1': {
			if(checkStatusC(apic))
				createEvent(apic);
			else
				cout << endl << "Sorry! You need to be contributor to create an event! " << endl;
			break;
		}
		case '2': {
			if(checkStatusC(apic))
				promoteEvent(apic);
			else
				cout << endl << "Sorry! You need to be contributor to promote an event! " << endl;
			break;
		}
		case '3': {
			searchEventByArea();
			break;
		}
		case '4': {
			//returns to previous menu
			return;
			break;
		}
		case '5': {
			cout << endl;
			//logs out user
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case '0': {
			cout << "See you soon!" << endl;
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}

void APIC::menuMessages(APIC apic) {
	char pick;

	do {
		cout << endl << "----Messages Menu----" << endl;
		cout << "Please choose what you want to do next: " << endl;
		cout << "1: Create a message" << endl;
		cout << "2: View my messages" << endl;
		cout << "3: Go to previous menu" << endl;
		cout << "4: To Log Out" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case '1': {
			if(checkStatusC(apic))
				createMessage(apic);
			else
				cout << endl << "Sorry! You need to be contributor to send messages! " << endl;
			break;
		}
		case '2': {
			if(checkStatusI(apic))
				cout << endl << "Sorry! Your account is inactive! You can't receive messages! " << endl;
			else
				printMessage(apic.getUserLogged());
			break;
		}
		case '3': {
			//returns to previous menu
			return;
			break;
		}
		case '4': {
			cout << endl;
			//logs user out
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case '0': {
			cout << "See you soon!" << endl;
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}
