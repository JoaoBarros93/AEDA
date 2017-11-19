#ifndef AREA_H_
#define AREA_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "exceptions.h"

using namespace std;

class Area{
private:
	string areaName;
	string subAreaName;
	string areaNameSigla;
	string subAreaNameSigla;
public:
	Area();
	Area(stringstream& s);
	string getAreaName();
	string getSubAreaName();
	string getAreaNameSigla();
	string getSubAreaNameSigla();
	vector <string> getUsersVector();
};

#endif /* AREA_H_ */
