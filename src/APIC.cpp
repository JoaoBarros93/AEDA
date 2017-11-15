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
			<< date << ";0;0;";

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

void APIC::loadEventsSS() {
	fstream eventsSSFile("eventsSS.txt");
	string line2;
	stringstream ss2;

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

void APIC::insertEventSS(EventSummerSchool newEventSS) {
	eventsSS.push_back(newEventSS);
}

void APIC::insertEventC(EventConference newEventC) {
	eventsC.push_back(newEventC);
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

	cout << endl << "For which area are you looking for sub areas?" << endl;
	cout << "Type ';' or ',' will return back. " << endl;
	cout << "Type 'area?' will show you all the areas available" << endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');
	if (area == "area?") {
		printAreasFull();
		cout << endl << "For which area are you looking for sub areas?" << endl;
		cout << "Type ';' or ',' will return back. " << endl;
		cout << "Your pick: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
	}

	if (findSemicolon(area))
		return;
	stringToUpper(area);
	cout << endl << "---Sub Areas of " << area << "---" << endl;
	printSubArea(area);
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
	}
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

void APIC::searchEventByArea() {
	string area;
	cout << endl
			<< "Please insert the acronym of the area you are looking for: "
			<< endl;
	cout << "Insert 'area?' will print all areas. Insert semicolon will return"
			<< endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');
	if (findSemicolon(area)) {
		return;
	}
	if (area == "area?") {
		printAreasFull();
		cout << endl
				<< "Please insert the acronym of the area you are looking for: "
				<< endl;
		cout << "Insert semicolon will return" << endl;
		cout << "Your pick: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
		if (findSemicolon(area)) {
			return;
		}
	}
	stringToUpper(area);

	for (unsigned int i = 0; i < eventsC.size(); i++) {
		cout << endl;
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

	for (unsigned int i = 0; i < eventsSS.size(); i++) {
		cout << endl;
		if (eventsSS[i].getArea() == area) {
			cout << "Event created by "
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
		}
	}
}

void APIC::searchUserByArea() {
	string area;
	vector<string> usersVector;
	cout << endl
			<< "Please insert the acronym of the area you are looking for: "
			<< endl;
	cout << "Insert 'area?' will print all areas. Insert semicolon will return"
			<< endl;
	cout << "Your pick: ";
	cin >> area;
	cin.clear();
	cin.ignore(10000, '\n');
	if (findSemicolon(area)) {
		return;
	}
	if (area == "area?") {
		printAreasFull();
		cout << endl
				<< "Please insert the acronym of the area you are looking for: "
				<< endl;
		cout << "Insert semicolon will return" << endl;
		cout << "Your pick: ";
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
		if (findSemicolon(area)) {
			return;
		}
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
			users[i].setStatus('c');
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

void APIC::promoteEvent(APIC apic) {
	string pick;
	unsigned int pick2;
	bool exit = 0;

	do {
		cout << endl
				<< "Do you want to promote a conference or a summer school "
				<< endl;
		cout << "'c' for conference or 'ss' for summer school" << endl;
		cin >> pick;
		cin.clear();
		cin.ignore(10000, '\n');

		if (pick == "c" || pick == "ss")
			exit = 1;
	} while (exit == 0);

	if (pick == "c") {
		printEventsC();
		do{cout << endl << "Insert the number of the event you want to promote:"
				<< endl;
		cout << "Your pick: ";
		cin >> pick2;
		cin.clear();
		cin.ignore(10000, '\n');}while(pick2<1 || pick2>eventsC.size());
		for (unsigned int i = 0; i < eventsC.size(); i++) {
			if (i + 1 == pick2) {
				eventsC[i].insertPromoter(apic.getUserLogged());
				//updatestatus
				remove("eventsC.txt");

				ofstream eventsCFile;
				eventsCFile.open("eventsC.txt");
				for (unsigned int i = 0; i < eventsC.size(); i++) {
					if (i + 1 != pick2) {
						eventsCFile
								<< eventsC[i].getUserCreated().getLoginName()
								<< ";" << eventsC[i].getLocal() << ";"
								<< eventsC[i].getTitle() << ";"
								<< eventsC[i].getDate().getDay() << "/"
								<< eventsC[i].getDate().getMonth() << "/"
								<< eventsC[i].getDate().getYear() << ";"
								<< eventsC[i].getArea() << ";"
								<< eventsC[i].getSupport() << ";"
								<< eventsC[i].getNumberPeople() << ";" << endl;
					}
					if (i + 1 == pick2) {
						eventsCFile
								<< eventsC[i].getUserCreated().getLoginName()
								<< ";" << eventsC[i].getLocal() << ";"
								<< eventsC[i].getTitle() << ";"
								<< eventsC[i].getDate().getDay() << "/"
								<< eventsC[i].getDate().getMonth() << "/"
								<< eventsC[i].getDate().getYear() << ";"
								<< eventsC[i].getArea() << ";"
								<< eventsC[i].getSupport() << ";"
								<< eventsC[i].getNumberPeople() << ";"
								<< apic.getUserLogged().getLoginName() << endl;
					}
				}
			}
		}
	}

	if (pick == "ss") {
		printEventsSS();
		do{cout << endl << "Insert the number of the event you want to promote:" << endl;
		cout << "Your title: ";
		cin >> pick2;
		cin.clear();
		cin.ignore(10000, '\n');}while(pick2<1 || pick2>(eventsSS.size()));
		for (unsigned int i = 0; i < eventsSS.size(); i++) {
			if (i + 1 == pick2) {
				eventsSS[i].insertPromoter(apic.getUserLogged());//aqui tem que checkar se existe
				//updatestatus
				remove("eventsSS.txt");

				ofstream eventsSSFile;
				eventsSSFile.open("eventsSS.txt");
				for (unsigned int i = 0; i < eventsSS.size(); i++) {
					if (i + 1 != pick2) {
						eventsSSFile
								<< eventsSS[i].getUserCreated().getLoginName()
								<< ";" << eventsSS[i].getLocal() << ";"
								<< eventsSS[i].getTitle() << ";"
								<< eventsSS[i].getDate().getDay() << "/"
								<< eventsSS[i].getDate().getMonth() << "/"
								<< eventsSS[i].getDate().getYear() << ";"
								<< eventsSS[i].getArea() << ";"
								<< eventsSS[i].getSupport() << ";";
						for (unsigned int j = 0;
								j < eventsSS[i].getFormers().size(); j++) {
							if (j + 1 == eventsSS[i].getFormers().size()) {
								eventsSSFile
										<< eventsSS[i].getFormers()[j].getLoginName()
										<< "," << endl;
							} else {
								eventsSSFile
										<< eventsSS[i].getFormers()[j].getLoginName()
										<< ";";
							}
						}
					}
					if (i + 1 == pick2) {
						eventsSSFile
								<< eventsSS[i].getUserCreated().getLoginName()
								<< ";" << eventsSS[i].getLocal() << ";"
								<< eventsSS[i].getTitle() << ";"
								<< eventsSS[i].getDate().getDay() << "/"
								<< eventsSS[i].getDate().getMonth() << "/"
								<< eventsSS[i].getDate().getYear() << ";"
								<< eventsSS[i].getArea() << ";"
								<< eventsSS[i].getSupport() << ";";

						for (unsigned int j = 0;
								j < eventsSS[i].getFormers().size(); j++) {
							if (j + 1 == eventsSS[i].getFormers().size()) {
								eventsSSFile
										<< eventsSS[i].getFormers()[j].getLoginName()
										<< ",";
							} else {
								eventsSSFile
										<< eventsSS[i].getFormers()[j].getLoginName()
										<< ";";
							}
						}
						eventsSSFile << apic.getUserLogged().getLoginName()
								<< endl;

					}
				}

			}
		}
	}
}

void APIC::createEvent(APIC apic) {
	int pick;
	do {
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

	do {
		cout << endl
				<< "Enter the scientific area of which your event is about: "
				<< endl;
		cout
				<< "Enter 'area?' to display all areas. Enter semicolon or comma will return back "
				<< endl;
		cout << "Your pick: " << endl;
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in area
		if (findSemicolon(area))
			return;

		if (area == "area?") {
			printAreasFull();
			cout << endl
					<< "Please insert the acronym of the area want to add: "
					<< endl;
			cout << "Insert semicolon will return" << endl;
			cout << "Your pick: ";
			cin >> area;
			cin.clear();
			cin.ignore(10000, '\n');
			if (findSemicolon(area)) {
				return;
			}

		}
		stringToUpper(area);
		if (checkArea(area)) {
			cout << "Area found and added! " << endl;
			exit = 1;
		} else
			cout << "Area not found! Please try again! " << endl;
	} while (exit == 0);

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

	EventSummerSchool newSummerSchool(apic.getUserLogged(), local, title, date,
			area, 0, formers);

	ofstream eventsSSFile;
	eventsSSFile.open("eventsSS.txt", ofstream::app);
	eventsSSFile << apic.getUserLogged().getLoginName() << ";" << local << ";"
			<< title << ";" << date.getDay() << "/" << date.getMonth() << "/"
			<< date.getYear() << ";" << area << ";" << 0 << ";";

	for (unsigned int i = 0; i < formers.size(); i++) {
		if (i + 1 == formers.size()) {
			eventsSSFile << formers[i].getLoginName() << "," << endl;
		} else {
			eventsSSFile << formers[i].getLoginName() << ";";
		}
	}

	eventsSSFile.close();

}

void APIC::createConference(APIC apic) {
	unsigned int numberPeople, error = 0;
	bool exit = 0;
	string local, dateString, newFormer, title, area;

	do {
		cout << endl
				<< "Enter the scientific area of which your event is about: "
				<< endl;
		cout
				<< "Enter 'area?' to display all areas. Enter semicolon or comma will return back "
				<< endl;
		cout << "Your pick: " << endl;
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in area
		if (findSemicolon(area))
			return;

		if (area == "area?") {
			printAreasFull();
			cout << endl
					<< "Please insert the acronym of the area want to add: "
					<< endl;
			cout << "Insert semicolon will return" << endl;
			cout << "Your pick: ";
			cin >> area;
			cin.clear();
			cin.ignore(10000, '\n');
			if (findSemicolon(area)) {
				return;
			}

		}
		stringToUpper(area);
		if (checkArea(area)) {
			cout << "Area found and added! " << endl;
			exit = 1;
		} else
			cout << "Area not found! Please try again! " << endl;
	} while (exit == 0);

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

	EventConference newConference(apic.getUserLogged(), local, title, date,
			area, 0, numberPeople);

	ofstream eventsCFile;
	eventsCFile.open("eventsC.txt", ofstream::app);
	eventsCFile << apic.getUserLogged().getLoginName() << ";" << local << ";"
			<< title << ";" << date.getDay() << "/" << date.getMonth() << "/"
			<< date.getYear() << ";" << area << ";0;" << numberPeople << ";"
			<< endl;

	eventsCFile.close();
}

void APIC::createMessage(APIC apic){
	bool exit = 0, skip=0, find=0;
	int pick;
	string areaString,msg;
	vector<string> areasS;
	vector<User> receivers;
	do {
		cout << endl << "Please insert the area that you want to share this message with: " << endl;
		cout << "Enter 'area?' to display all areas. " << endl;
		cout << "Enter 'all' will share this message with all areas " << endl;
		cout << "Enter semicolon or comma will return back "<< endl;
		cout << "Your pick: " << endl;
		cin >> areaString;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in area
		if (findSemicolon(areaString))
			return;

		if (areaString == "area?") {
			printAreasFull();
			cout << endl<< "Please insert the acronym of the area want to add: " << endl;
			cout << "Insert semicolon will return" << endl;
			cout << "Your pick: ";
			cin >> areaString;
			cin.clear();
			cin.ignore(10000, '\n');
			if (findSemicolon(areaString)) {
				return;
			}
		}

		if(areaString=="all"){
			cout << "This message will be sent to every area! " << endl;
			skip=1;
			exit=1;
		}

		if (skip == 0) {
			stringToUpper(areaString);
			if (checkArea(areaString)) {
				areasS.push_back(areaString);
				cout << "Area found and added! " << endl;
				cout << "Do you want to add another area?" << endl;
				cout << "1: Yes" << endl << "2: No" << endl;
				cin >> pick;
				cin.clear();
				cin.ignore(10000, '\n');
				if(pick==2)
					exit=1;
				else if(pick!=1)
					cout << "Wrong input! Will assume you don't want to add more areas! " << endl;
			} else
				cout << "Area not found! Please try again! " << endl;
		}
	} while (exit == 0);

	cout << endl << "Insert your message: " << endl;
	cout << "Message: ";
	getline(cin,msg);

	Date todayDate=getTodayDate();

	if(areaString == "all"){
		for(unsigned int i =0;i<users.size();i++){
			if(users[i].getStatus()=='c' || users[i].getStatus()=='s')
				receivers.push_back(users[i]);
		}
	}
	else {
		for (unsigned int i = 0; i < areasS.size(); i++) {
			for (unsigned int j = 0; j < users.size(); j++) {
				find = 0;
				for (unsigned int k = 0; k < users[j].getVectorAreas().size();
						k++) {
					if (areasS[i]
							== users[j].getVectorAreas()[k].getAreaNameSigla()) {
						for (unsigned int l = 0; l < receivers.size(); l++) {
							if (receivers[l].getLoginName()== users[j].getLoginName())
								find = 1;
						}
						if (find == 0) {
							receivers.push_back(users[j]);
						}
					}
				}
			}
		}
	}

	//increments the number of messages this user has sent
	for(unsigned int i=0;i<users.size();i++){
		if(apic.getUserLogged().getLoginName()==users[i].getLoginName())
			users[i].setSent(users[i].getSent()+1);
	}

	//increments the number of messages received for all users that will receive this message
	for(unsigned int i =0;i<receivers.size();i++){
		for(unsigned int j =0;j<users.size();j++){
			if(receivers[i].getLoginName()==users[j].getLoginName()){
				users[j].setReceived(users[j].getReceived()+1);
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

	usersFile.close();

	//creates the message and puts it in messages vector
	Message newMessage(apic.getUserLogged(), todayDate, msg, receivers);
	messages.push_back(newMessage);

	//writes to the msg.txt
	ofstream msgFile;
	msgFile.open("msg.txt", ofstream::app);
	msgFile << apic.getUserLogged().getLoginName() << ";" << todayDate.getDay()
			<< "/" << todayDate.getMonth() << "/" << todayDate.getYear() << ";"
			<< msg << ";";
	if (receivers.size() == 0)
		msgFile << endl;

	for (unsigned int i = 0; i < receivers.size(); i++) {
		if (i + 1 == receivers.size())
			msgFile << receivers[i].getLoginName() << "," << endl;
		else
			msgFile << receivers[i].getLoginName() << ";";
	}

	msgFile.close();

}

EventSummerSchool APIC::readSummerSchool(stringstream & s) {
	string newUserString, newDateString, newLocal, newTitle, newArea,
			newSupportString, newFormersString;
	int newSupport;
	User newUser;
	vector<User> newFormers;

	//read user
	if (!getline(s, newUserString, ';'))
		cout << "Error getting user" << endl;

	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == newUserString)
			newUser = users[i];
	}

	//read local
	if (!getline(s, newLocal, ';'))
		cout << "Error getting local" << endl;

	//read title
	if (!getline(s, newTitle, ';'))
		cout << "Error getting title" << endl;

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error getting date" << endl;

	Date newDate(newDateString);

	//read area
	if (!getline(s, newArea, ';'))
		cout << "Error getting area" << endl;

	//read support status
	if (!getline(s, newSupportString, ';'))
		cout << "Error getting support status" << endl;

	newSupport = stoi(newSupportString);

	//read all formers
	if (!getline(s, newFormersString, ','))
		cout << "Error getting former" << endl;

	istringstream iss(newFormersString);
	string formerLoginName;
	while (getline(iss, formerLoginName, ';')) {
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i].getLoginName() == formerLoginName) {
				newFormers.push_back(users[i]);
			}
		}
	}

	EventSummerSchool newSS(newUser, newLocal, newTitle, newDate, newArea,
			newSupport, newFormers);
	return newSS;
}

EventConference APIC::readConference(stringstream & s) {
	string newUserString, newDateString, newLocal, newTitle, numberString,
			newArea, newSupportString;
	int newNumber, newSupport;
	User newUser;

	//read user
	if (!getline(s, newUserString, ';'))
		cout << "Error getting user" << endl;

	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == newUserString)
			newUser = users[i];
	}

	//read local
	if (!getline(s, newLocal, ';'))
		cout << "Error getting local" << endl;

	//read title
	if (!getline(s, newTitle, ';'))
		cout << "Error getting title" << endl;

	//read date as a string
	if (!getline(s, newDateString, ';'))
		cout << "Error getting date" << endl;

	Date newDate(newDateString);

	//read area
	if (!getline(s, newArea, ';'))
		cout << "Error getting area" << endl;

	//read support status
	if (!getline(s, newSupportString, ';'))
		cout << "Error getting support status" << endl;

	newSupport = stoi(newSupportString);

	//read all formers
	if (!getline(s, numberString, ';'))
		cout << "Error getting number of people" << endl;

	newNumber = stoi(numberString);

	EventConference newC(newUser, newLocal, newTitle, newDate, newArea,
			newSupport, newNumber);
	return newC;
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
				cout << "Success! Account created!" << endl;
				cout << "Pay your annual quota for full access!" << endl
						<< endl;
			}

			pick = 3;
			break;
		}
		case 0:
			exit(EXIT_FAILURE);
		default:
			cout << "Wrong pick! Please pick again" << endl << endl;
			break;
		}
	} while (true);
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
			menuMessages(apic);
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
			searchEventByArea();
			break;
		}
		case 7: {
			cout << endl;
			printAreasFull();
			break;
		}
		case 8: {
			cout << endl;
			printAreasSiglas();
			break;
		}
		case 9: {
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
			promoteEvent(apic);
			break;
		}
		case 3: {
			searchEventByArea();
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

void APIC::menuMessages(APIC apic) {
	int pick;

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
		case 1: {
			createMessage(apic);
			break;
		}
		case 2: {

			break;
		}
		case 3: {
			return;
			break;
		}
		case 4: {
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


