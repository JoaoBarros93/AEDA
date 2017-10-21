#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "functions.h"

using namespace std;



int main() {

	vector<User > users;
	fstream usersFile("users.txt");
	string line;
	stringstream ss;


	while (usersFile.good())
	{
	    ss.clear();
	    getline(usersFile,line,'\n');
	    ss << line;
	    User newUser(ss);
	    users.push_back(newUser);
	}

	Menu1(users);


	return 0;
}
