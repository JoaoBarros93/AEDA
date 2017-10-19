#include "functions.h"
#include "user.h"
#include <stdlib.h>


using namespace std;

void Login(int n){
	string username, password, un, pw;
	int loginTry = n;

	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	ifstream read(username + ".txt");
	getline(read,un);
	getline(read,pw);

	if(username == un && password == pw){
		User *userLogged = new User(username);
		cout << "Login Successful!" << endl;
		Menu2(*userLogged);
	}
	else {
		cout << endl <<"ERROR: Wrong username or password! " << endl;
		loginTry++;
		if(loginTry < 3)Login(loginTry);
		else{
			cout << "ERROR: You failed to login to many times!" << endl << endl;
			system("exit");
		}
	}
}

void Register(){
	string username, password, institution;

	cout << "Select your username: " << endl;
	cin >> username;
	cout << "Select your password: " << endl;
	cin >> password;
	cout << "Select your institution: " << endl;
	cin >> institution;

	ofstream file;
	ofstream usersFile;

	file.open(username + ".txt");
	file << username << endl << password << endl << institution;
	file.close();
	usersFile.open("users.txt");
	usersFile << username << endl;
	usersFile.close();


	cout << "Sucess! Account created!" << endl << endl;
	Menu1();
}

void Menu1(){
	int pick;

		cout << "Welcome! " << endl;
		cout << "Please press:" << endl;
		cout << "1: To login" << endl;
		cout << "2: To register" << endl;
		cin >> pick;

		switch(pick){
		case 1:
			Login(0);
			break;
		case 2:
			Register();
			break;
		default:
			cout << "Wrong pick! Please pick again";
			Menu1();
		}
}


void Menu2(User user){
	int pick;

	cout << "Welcome " << user.getLoginName() << endl;
	cout << "Please choose what you want to do next: "<< endl;
	cout << "1: See all other users" << endl;
	cout << "2: Search for an user" << endl;
	cout << "3: Search for an event " << endl;
	cout << "4: Create an event " << endl;
	cout << "5: Promote an event " << endl;
	cout << "6: Pay my quota " << endl;
	cout << "0: To Log Out" << endl;
	cout << "00: To exit" << endl;
	cin >> pick;

	switch(pick){
	case 0:
		Menu1();
		break;
	}
}

