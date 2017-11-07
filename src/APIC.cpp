#include "APIC.h"
using namespace std;

APIC::APIC() {

	//read areas file and populate areas vector
	loadAreas();

	//read users file and populate users vector
	loadUsers();

	//read events file and populate events vector
	//loadEvents();

}

bool APIC::login(int n, APIC apic) {
	APIC apic_ = apic;
	ifstream usersFile("users.txt");

	string username, password;
	int loginTry = n;

	cout << endl << "Enter username (semicolon or comma will exit):";
	cin >> username;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in username
	if (findSemicolon(username))
		menu1(apic);

	cout << "Enter password (semicolon or comma will exit) ";
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in username
	if (findSemicolon(password))
		menu1(apic);

	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == username
				&& users[i].getPassword() == password) {
			users[i].login();
			apic.setUserLogged(users[i]);
			cout << "Login Sucessful!" << endl;
			menu2(apic);
		}
	}

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
	string username, password, institution, areaCompleteString;
	string date = "1/1/1900";
	vector<string> areaVector;
	int pick, pick2;
	string area, subarea;
	bool exit = false, exit2 = false;
	stringstream ss;
	stringstream areaComplete;

	cout << endl << "Select your username (semicolon or comma will exit): "
			<< endl;
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

	cout << endl << "Select your password (semicolon or comma will exit): "
			<< endl;
	cout << "Password: ";
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in password
	if (findSemicolon(password))
		menu1(apic);

	cout << endl << "Select your institution (semicolon or comma will exit): "
			<< endl;
	cout << "Institution: ";
	cin >> institution;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in institution
	if (findSemicolon(institution))
		menu1(apic);

	do {
		do {

			cout << endl
					<< "How do you want to visualize the areas of interest?"
					<< endl;
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

		do {
			cout << endl << "Please choose the area you want to add: " << endl;
			cout << "Your area: ";
			cin >> area;
			cin.clear();
			cin.ignore(10000, '\n');
			if (findSemicolon(area))
				menu1(apic);
			stringToUpper(area);

			if (checkArea(area)) {
				cout << endl << "Now please pick a sub area: " << endl;
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
					cout
							<< "Do you want to add another area (1 for yes, anything else for no) ?"
							<< endl;
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
	ss << date << ";";

//file with users names for output
	ofstream usersFile;
	usersFile.open("users.txt", ofstream::app);
	usersFile << username << ";" << password << ";" << institution << ";"
			<< date << ";";

	for (unsigned int i = 0; i < areaVector.size(); i++) {
		if (i + 1 == areaVector.size()) {
			usersFile << areaVector[i] << "," << endl;
			ss << areaVector[i] << "," << endl;
		} else {
			usersFile << areaVector[i] << ";";
			ss << areaVector[i] << ";";
		}
	}

	User newUser(ss, areas);
	users.push_back(newUser);

	usersFile.close();
	return true;
}

//LOAD FUNCTIONS
void APIC::loadUsers() {
	fstream usersFile("users.txt");
	string line;
	stringstream ss;

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

/*void APIC::loadEvents() {
	fstream eventsFile("events.txt");
	string type, line2;
	stringstream ss, ss2;

	while (eventsFile.good()) {
		ss2.clear();
		getline(eventsFile, line2, '\n');
		if (line2 != "") {
			ss2 << line2;
			if (!getline(ss2, type, ';'))
				cout << "Error getting type from event" << endl;
			if (type == "c")
				EventConference newConference(ss2);

			else if (type == "s")
				EventSummerSchool newSummerSchool(ss2);

			else
				cout << "ERROR! Error reading events!" << endl;
		}
	}
}*/

//GET FUNCTIONS
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

//SET FUNCTIONS
void APIC::setUserLogged(User userLogged) {
	this->userLogged = userLogged;
}

void APIC::insertUser(User newuser) {
	users.push_back(newuser);
}

void APIC::insertArea(Area newArea) {
	areas.push_back(newArea);
}

void APIC::insertEvent(Event newEvent) {
	events.push_back(newEvent);
}

//PRINT FUNCTIONS
void APIC::printUsers() {
	cout << "All users: " << endl;
	for (unsigned int i = 0; i < users.size(); i++) {
		cout << users[i].getLoginName() << endl;
	}
}

void APIC::printUsersComplete() {
	cout << endl << "Complete info of all users: " << endl << endl;
	for (unsigned int i = 0; i < users.size(); i++) {
		cout << "----" << "User" << i + 1 << "----" << endl;
		cout << "Login name: " << users[i].getLoginName() << endl;
		cout << "Institution: " << users[i].getInstitution() << endl;
		cout << "Date of last quota payment: " << users[i].getDateString()
				<< endl;
		for (unsigned int j = 0; j < users[i].getVectorAreasString().size();
				j++) {
			cout << "Area" << j + 1 << " " << users[i].getVectorAreasString()[j]
					<< endl;
		}

		cout << endl;
	}
}

void APIC::printAreasFull() {
	cout << "----AREAS----" << endl;
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (i != 0) {
			if (areas[i].getAreaName() != areas[i - 1].getAreaName())
				cout << areas[i].getAreaName() << " - "
						<< areas[i].getAreaNameSigla() << endl;
		}
	}
}

void APIC::printAreasSiglas() {
	cout << "----AREAS----" << endl;
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (i != 0) {
			if (areas[i].getAreaNameSigla() != areas[i - 1].getAreaNameSigla())
				cout << areas[i].getAreaNameSigla() << endl;
		}
	}
}

void APIC::printSubArea(string area) {
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (areas[i].getAreaNameSigla() == area) {
			cout << areas[i].getSubAreaName() << " - "
					<< areas[i].getSubAreaNameSigla() << endl;
		}
	}
}

void APIC::printSubAreasUser() {
	string area;
	do {
		cout << endl << "For which area are you looking for sub areas?" << endl;
		cout << "Type ';' or ',' will return back. " << endl;
		cout << "Type 'area?' will show you all the areas available" << endl;
		cout << "Your pick: ";
		cin >> area;
		if (area == "area?")
			printAreasFull();

		cin.clear();
		cin.ignore(10000, '\n');
		if (findSemicolon(area))
			return;
		printSubArea(area);
	} while (true);

}

//SEARCH FUNCTIONS
void APIC::searchUser() {
	string user;
	cout << "Please, insert the login name of the user you are trying to find: "
			<< endl;
	cout << "Your pick: ";
	cin >> user;
	cin.clear();
	cin.ignore(10000, '\n');

	for (unsigned int i = 0; i < users.size(); i++) {

		if (users[i].getLoginName() == user) {
			cout << "User found! " << endl;
			cout << "Login name: " << users[i].getLoginName() << endl;
			cout << "Institution: " << users[i].getInstitution() << endl;
			cout << "Scientific areas of interest: " << endl;
			for (unsigned int j = 0; j < users[i].getVectorAreas().size();
					j++) {
				cout << users[i].getVectorAreasString()[j] << endl;
			}
		}
	}
}

void APIC::searchEvent() {
}

void APIC::searchUserByArea() {
	string area;
	vector<string> usersVector;
	cout << "Please insert the sigla of the area you are looking for: " << endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');
	if (findSemicolon(area)) {
		return;
	}
	cout << "Users in that area: " << endl;

	for (unsigned int i = 0; i < users.size(); i++) {
		for (unsigned int j = 0; j < users[i].getVectorAreas().size(); j++) {
			if (users[i].getVectorAreas()[j].getAreaNameSigla() == area) {
				usersVector.push_back(users[i].getLoginName());
			}
		}
	}

//we use this to print only different elements
	auto last = unique(usersVector.begin(), usersVector.end());
	usersVector.erase(last, usersVector.end());

	for (unsigned int i = 0; i < usersVector.size(); i++) {
		cout << usersVector[i] << endl;
	}
}

void APIC::searchUserBySubArea() {
	string area;
	vector<string> usersVector;
	cout
			<< "Please insert the sigla of the area and subarea you want to search in the format: 'XXX-XXX':"
			<< endl;
	cout << "Your area and sub area: " << endl;
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');
//try to find ";" in username
	if (findSemicolon(area)) {
		return;
	}

	cout << "Users in that area: " << endl;

	for (unsigned int i = 0; i < users.size(); i++) {
		for (unsigned int j = 0; j < users[i].getVectorAreasString().size();
				j++) {
			if (users[i].getVectorAreasString()[j] == area) {
				usersVector.push_back(users[i].getLoginName());
			}
		}
	}

//we use this to print only different elements
	auto last = unique(usersVector.begin(), usersVector.end());
	usersVector.erase(last, usersVector.end());

	for (unsigned int i = 0; i < usersVector.size(); i++) {
		cout << usersVector[i] << endl;
	}
}

//CHECK FUNCTIONS
bool APIC::checkArea(string area) {
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (area == areas[i].getAreaNameSigla())
			return true;
	}
	return false;
}

bool APIC::checkSubArea(string subArea) {
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (subArea == areas[i].getSubAreaNameSigla())
			return true;
	}
	return false;
}

bool APIC::findSemicolon(string stringToSearch) {
	basic_string<char>::size_type index1, index2, index3;
	static const basic_string<char>::size_type npos = -1;
	index1 = stringToSearch.find(';');
	index2 = stringToSearch.find(',');
	index3 = stringToSearch.find(' ');

	if (index1 != npos || index2 != npos || index3 != npos) {
		cout << "You returned back! " << endl << endl;
		return true;
	} else
		return false;
}

//OTHER FUNCTIONS
void APIC::payQuota(APIC apic) {
	Date todayDate = getTodayDate();
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == apic.getUserLogged().getLoginName()) {
			users[i].setDatePay(todayDate);
		}
	}

	remove("users.txt");

	ofstream usersFile;
	usersFile.open("users.txt");
	for (unsigned int i = 0; i < users.size(); i++) {
		usersFile << users[i].getLoginName() << ";" << users[i].getPassword()
				<< ";" << users[i].getInstitution() << ";"
				<< users[i].getDatePay().getDay() << "/"
				<< users[i].getDatePay().getMonth() << "/"
				<< users[i].getDatePay().getYear() << ";";

		for (unsigned int j = 0; j < users[i].getVectorAreasString().size();
				j++) {
			if (j + 1 == users[i].getVectorAreasString().size()) {
				usersFile << users[i].getVectorAreas()[j].getAreaNameSigla()
						<< "-"
						<< users[i].getVectorAreas()[j].getSubAreaNameSigla()
						<< "," << endl;
			} else {
				usersFile << users[i].getVectorAreas()[j].getAreaNameSigla()
						<< "-"
						<< users[i].getVectorAreas()[j].getSubAreaNameSigla()
						<< ";";
			}
		}
	}

	cout << "Thank you!" << endl;
	cout << "Your quota has been paid. You have now full access! " << endl;
}

void APIC::stringToUpper(string &s) {
	for (unsigned int l = 0; l < s.length(); l++) {
		s[l] = toupper(s[l]);
	}
}

void APIC::promoteEvent() {

}

void APIC::createEvent(APIC apic) {
	int pick;
	do {
		cout << endl <<  "What type of event do you want to create? " << endl;
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
	string local, dateString, newFormer, title;
	vector<User> formers;

	cout
			<< "Where will the event take place? (semicolon will return back. Please do not use spaces) "
			<< endl;
	cin >> local;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in local
	if (findSemicolon(local))
		return;

	do {
		cout
				<< "In which date will the event take place? (format: 'dd/mm/yyyy' Semicolon will return back) "
				<< endl;
		cin >> dateString;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in dateString
		if (findSemicolon(dateString))
			return;

		Date date(dateString);
		if (!date.isFuture()) {
			cout << "ERROR! You need to enter a future date!" << endl;
			error = 1;
		} else
			error = 0;
	} while (error == 1);

	Date date(dateString);

	cout
			<< "Please insert a title for the event: (Semicolon will return back. Please do not use spaces) "
			<< endl;
	cin >> title;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in title
	if (findSemicolon(title))
		return;

	cout << endl;
	printUsers();
	cout << endl;
	do {
		ok = 1;
		cout
				<< "Insert the name of the user you want to add as former: (Semicolon will return back) "
				<< endl;
		cin >> newFormer;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in newFormer
		if (findSemicolon(newFormer))
			return;
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == newFormer) {
				formers.push_back(users[i]);
				ok = 0;
			}
		}
		if (ok == 1)
			cout << "Sorry. Could not find your user. " << endl;
		cout << "Do you want to add more formers? (1 for yes or 2 for no)"
				<< endl;
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	} while (pick == 1);
	if (ok == 0)
		cout << "Success! Event created! " << endl;

	EventSummerSchool newSummerSchool('s', apic.getUserLogged(),local, title, date, formers);

	ofstream eventsFile;
	eventsFile.open("events.txt", ofstream::app);
	eventsFile << "s;" << apic.getUserLogged().getLoginName() << ";" << local
			<< ";" << title << ";" << date.getDay() << "/" << date.getMonth()
			<< "/" << date.getYear() << ";";

	for (unsigned int i = 0; i < formers.size(); i++) {
		if (i + 1 == formers.size()) {
			eventsFile << formers[i].getLoginName() << ";" << endl;
		} else {
			eventsFile << formers[i].getLoginName() << ",";
		}
	}

	eventsFile.close();

}

void APIC::createConference(APIC apic) {
	unsigned int numberPeople, error = 0;
	string local, dateString, newFormer, title;

	cout << "Where will the event take place? (Semicolon will return back)"
			<< endl;
	cin >> local;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in local
	if (findSemicolon(local))
		return;

	do {
		cout
				<< "In which date will the event take place? (format: 'dd/mm/yyyy' Semicolon will return back) "
				<< endl;
		cin >> dateString;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in dateString
		if (findSemicolon(dateString))
			return;

		Date date(dateString);
		if (!date.isFuture()) {
			cout << "ERROR! You need to enter a future date!" << endl;
			error = 1;
		} else
			error = 0;
	} while (error == 1);

	Date date(dateString);

	cout
			<< "Please insert a title for the event: (Semicolon will return back. Please dont use spaces) "
			<< endl;
	cin >> title;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in title
	if (findSemicolon(title))
		return;

	cout
			<< "Please insert the number of people you think that will show for this event: "
			<< endl;
	cin >> numberPeople;
	if (cin.fail())
		cout << "ERROR! Wrong input! " << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Success! Event created! " << endl;
	cout << "You can now message other users to promote your event!" << endl;

	EventConference newConference('c', apic.getUserLogged(),local, title, date, numberPeople);

	ofstream eventsFile;
	eventsFile.open("events.txt", ofstream::app);
	eventsFile << "c;" << apic.getUserLogged().getLoginName() << ";" << local
			<< ";" << title << ";" << date.getDay() << "/" << date.getMonth()
			<< "/" << date.getYear() << ";" << numberPeople << endl;

	eventsFile.close();

}

//MENUS
void APIC::menu1(APIC apic) {

	int pick;
	do {
		cout << "Welcome! " << endl;
		cout << "Please press:" << endl;
		cout << "1: To login" << endl;
		cout << "2: To register" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case 1:
			apic.login(3, apic);
			break;
		case 2: {
			bool reg = apic.regist(apic);
			if (reg) {
				cout << "Sucess! Account created!" << endl;
				cout << "Pay your anual quota for full acess!" << endl << endl;
			}

			pick = 3;
			break;
		}
		case 0:
			exit(EXIT_FAILURE);
		default:
			cout << "Wrong pick! Please pick again" << endl;
			break;
		}
	} while (pick <= 0 || pick > 2);
}

void APIC::menu2(APIC apic) {

	int pick;

	do {
		cout << endl << "Welcome " << apic.getUserLogged().getLoginName()
				<< endl;
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
		case 1: {
			menuSearch(apic);
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			menuEvents(apic);
			break;
		}

		case 4: {
			payQuota(apic);
			break;
		}
		case 5: {
			cout << endl;
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case 0: {
			cout << "See you soon!" << endl;
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}

void APIC::menuSearch(APIC apic) {
	int pick;

	do {
		cout << endl << "----Search and Print Menu----" << endl;
		cout << "Please choose what you want to do next: " << endl;
		cout << "1: See all other users names" << endl;
		cout << "2: See every information of all users" << endl;
		cout << "3: Search for an user by its name" << endl;
		cout << "4: Search for all users in an area" << endl;
		cout << "5: Search for all users in an subarea" << endl;
		cout << "6: Search for an event" << endl;
		cout << "7: Print all areas of interest with complete information "
				<< endl;
		cout << "8: Print all areas of interest, but just siglas " << endl;
		cout << "9: Look for the subareas of an area" << endl;
		cout << "10: Go to previous menu" << endl;
		cout << "11: To Log Out" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
		if (cin.fail())
			cout << "ERROR! Wrong input! " << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case 1: {
			printUsers();
			break;
		}
		case 2: {
			printUsersComplete();
			break;
		}
		case 3: {
			searchUser();
			break;
		}
		case 4: {
			cout << endl;
			searchUserByArea();
			break;
		}
		case 5: {
			cout << endl;
			searchUserBySubArea();
			break;
		}
		case 6: {
			cout << endl;
			printAreasFull();
			break;
		}
		case 7: {
			cout << endl;
			printAreasSiglas();
			break;
		}
		case 8: {
			cout << endl;
			printSubAreasUser();
			break;
		}
		case 10: {
			return;
			break;
		}
		case 11: {
			cout << endl;
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case 0: {
			cout << "See you soon!" << endl;
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}

void APIC::menuEvents(APIC apic) {
	int pick;

	do {
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
		case 1: {
			createEvent(apic);
			break;
		}
		case 2: {
			promoteEvent();
			break;
		}
		case 3: {
			searchEvent();
			break;
		}
		case 4: {
			return;
			break;
		}
		case 5: {
			cout << endl;
			apic.getUserLogged().logout();
			menu1(apic);
			break;
		}
		case 0: {
			cout << "See you soon!" << endl;
			exit(EXIT_FAILURE);
			break;
		}
		}
	} while (true);
}

