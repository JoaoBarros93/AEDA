#include "functions.h"
#include "user.h"
#include <stdlib.h>
#include <vector>

using namespace std;

void Login(int n, vector<User> &users) {
	ifstream usersFile("users.txt");

	string username, password;
	int loginTry = n;

	cout << "Enter username: ";
	cin >> username;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Enter password: ";
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');

	for(unsigned int i = 0; i<users.size();i++){
		if(users[i].getLoginName() == username && users[i].getPassword()==password){
			users[i].login();
			cout << "Login Sucessful!" <<endl;
			Menu2(users[i], users);
		}
	}

	cout << "ERROR: Wrong username or password! " << endl;
	cout << "You have " << loginTry << " tries left!" << endl;
	loginTry--;
	if(loginTry > 0){
		Login(loginTry, users);
	}
	else{
		cout << "ERROR: You failed to login to many times!" << endl << endl;
		exit (EXIT_FAILURE);
	}
}

bool Register(vector<User> &users) {
	string username, password, institution;
	stringstream ss;

	cout << "Select your username: " << endl;
	cin >> username;
	cin.clear();
	cin.ignore(10000, '\n');
	ss << username << ";";


	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].getLoginName() == username) {
			cout << "ERRO! Username is taken!" << endl << endl;
			Menu1(users);
		}
	}

	cout << "Select your password: " << endl;
	cin >> password;
	cin.clear();
	cin.ignore(10000, '\n');
	ss << password << ";";

	cout << "Select your institution: " << endl;
	cin >> institution;
	cin.clear();
	cin.ignore(10000, '\n');
	ss << institution;

	User newUser(ss);
	users.push_back(newUser);

	//file with users names for output
	ofstream usersFile;
	usersFile.open("users.txt", ofstream::app);
	usersFile << username << ";" << password << ";" << institution << endl;
	usersFile.close();

	return true;
}

void Menu1(vector<User> &users) {
	int pick;

	do {
		cout << "Welcome! " << endl;
		cout << "Please press:" << endl;
		cout << "1: To login" << endl;
		cout << "2: To register" << endl;
		cout << "0: To exit" << endl;
		cin >> pick;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (pick) {
		case 1:
			Login(3, users);
			break;
		case 2: {
			bool reg = Register(users);
			if (reg)
				cout << "Sucess! Account created!" << endl << endl;
			pick = 3;
			break;
		}
		case 0:
			exit (EXIT_FAILURE);
		default:
			cout << "Wrong pick! Please pick again" << endl;
			break;
		}
	} while (pick <= 0 || pick > 2);

}

void Menu2(User user, vector<User> &users) {
	int pick;

	cout << "Welcome " << user.getLoginName() << endl;
	cout << "Please choose what you want to do next: " << endl;
	cout << "1: See all other users" << endl;
	cout << "2: Search for an user" << endl;
	cout << "3: Search for an event " << endl;
	cout << "4: Create an event " << endl;
	cout << "5: Promote an event " << endl;
	cout << "6: Pay my quota " << endl;
	cout << "7: To Log Out" << endl;
	cout << "0: To exit" << endl;
	cin >> pick;
	cin.clear();
	cin.ignore(10000, '\n');

	switch (pick) {
	case 7:
		Menu1(users);
		break;
	case 0:
	{
		exit(EXIT_FAILURE);
		break;
	}
	}
}

