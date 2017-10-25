#include "APIC.h"
using namespace std;

APIC::APIC() {
	fstream usersFile("users.txt");
	string line;
	stringstream ss;

	while (usersFile.good()) {
		ss.clear();
		getline(usersFile, line, '\n');
		if (line != "") {
			ss << line;
			User newUser(ss);
			insertUser(newUser);
		}
	}
}

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
		cout << "1: See all other users names" << endl;
		cout << "2: See every information of all users" << endl;
		cout << "3: Search for an user" << endl;
		cout << "4: Search for an event " << endl;
		cout << "5: Create an event " << endl;
		cout << "6: Promote an event " << endl;
		cout << "7: Pay my quota " << endl;
		cout << "8: To Log Out" << endl;
		cout << "0: To exit" << endl;
		cout << "Your pick: ";
		cin >> pick;
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
		case 8: {
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

bool APIC::findSemicolon(string stringToSearch) {
	basic_string<char>::size_type index1, index2, index3;
	static const basic_string<char>::size_type npos = -1;
	index1 = stringToSearch.find(';');
	index2 = stringToSearch.find(',');
	index3 = stringToSearch.find(' ');

	if (index1 != npos || index2 != npos || index3 != npos ) {
		cout << "ERROR! Wrong input! " << endl;
		return true;
	} else
		return false;
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
	string username, password, institution, area;
	vector<string> areaVector;
	int pick;
	stringstream ss;

	cout << "Select your username (semicolon or comma will exit): " << endl;
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

	cout << "Select your password (semicolon or comma will exit): " << endl;
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in password
	if (findSemicolon(password))
		menu1(apic);

	cout << "Select your institution (semicolon or comma will exit): " << endl;
	cin >> institution;
	cin.clear();
	cin.ignore(10000, '\n');
	//try to find ";" in institution
	if (findSemicolon(institution))
		menu1(apic);

	do {
		cout << "Select your area of interest (semicolon or comma will exit): " << endl;
		cin >> area;
		cin.clear();
		cin.ignore(10000, '\n');
		//try to find ";" in area
		if (findSemicolon(area))
			menu1(apic);

		cout << "Press '1' to add another area or something else to continue "
				<< endl;
		cin >> pick;

		areaVector.push_back(area);
	} while (pick == 1);

	ss << username << ";";
	ss << password << ";";
	ss << institution << ";";

	//file with users names for output
	ofstream usersFile;
	usersFile.open("users.txt", ofstream::app);
	usersFile << username << ";" << password << ";" << institution << ";";

	for (unsigned int i = 0; i < areaVector.size(); i++) {
		if (i + 1 == areaVector.size()) {
			usersFile << areaVector[i] << "," << endl;
			ss << areaVector[i] << "," << endl;
		} else {
			usersFile << areaVector[i] << ";";
			ss << areaVector[i] << ";";
		}
	}

	User newUser(ss);
	users.push_back(newUser);

	usersFile.close();
	return true;
}

void APIC::setUserLogged(User userLogged) {
	this->userLogged = userLogged;
}

void APIC::insertUser(User newuser) {
	users.push_back(newuser);
}

User APIC::getUserLogged() {
	return userLogged;
}

bool APIC::getStatus() {
	return userLoggedStatus;
}

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
		for (unsigned int j = 0; j < users[i].getVectorAreas().size(); j++) {
			cout << "Area" << j+1 << " " << users[i].getVectorAreas()[j] << endl;
		}
		cout << endl;
	}
}

void APIC::searchUser() {
	string user;
	cout << "Please, insert the login name of the user you are trying to find: "
			<< endl;
	cin >> user;
	cin.clear();
	cin.ignore(10000, '\n');

	for (unsigned int i = 0; i < users.size(); i++) {

		if (users[i].getLoginName() == user) {
			cout << "User found! " << endl;
			cout << "Login name: " << users[i].getLoginName() << endl;
			cout << "Institution: " << users[i].getInstitution() << endl;
			cout << "Scientific areas of interest: " << endl;
			for (unsigned int j = 0; j < users[i].getVectorAreas().size();j++) {
				cout << users[i].getVectorAreas()[j] << endl;
			}
		}
	}
}
