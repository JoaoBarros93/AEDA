#include "area.h"

Area::Area(){
}

Area::Area(stringstream& s) {
	string newAreaName, newSubAreaName, newAreaNameSigla, newSubAreaNameSigla;

	if (!getline(s, newAreaName, ';'))
		cout << "Error getting area name" << endl;

	this->areaName = newAreaName;

	if (!getline(s, newSubAreaName, ';'))
		cout << "Error getting sub area name" << endl;

	this->subAreaName = newSubAreaName;

	if (!getline(s, newAreaNameSigla, ';'))
		cout << "Error getting area name acronym" << endl;

	this->areaNameSigla = newAreaNameSigla;

	if (!getline(s, newSubAreaNameSigla, ';'))
		cout << "Error getting sub area name acronym" << endl;

	this->subAreaNameSigla = newSubAreaNameSigla;
}

string Area::getAreaName() {
	return areaName;
}

string Area::getSubAreaName(){
	return subAreaName;
}

string Area::getAreaNameSigla(){
	return areaNameSigla;
}

string Area::getSubAreaNameSigla(){
	return subAreaNameSigla;
}
