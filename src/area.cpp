#include "area.h"

Area::Area(){
}

Area::Area(stringstream& s) {
	string newAreaName, newSubAreaName, newAreaNameSigla, newSubAreaNameSigla;

	if (!getline(s, newAreaName, ';'))
		cout << "Error reading area name" << endl;

	this->areaName = newAreaName;

	if (!getline(s, newSubAreaName, ';'))
		cout << "Error reading sub area name" << endl;

	this->subAreaName = newSubAreaName;

	if (!getline(s, newAreaNameSigla, ';'))
		cout << "Error reading area name acronym" << endl;

	this->areaNameSigla = newAreaNameSigla;

	if (!getline(s, newSubAreaNameSigla, ';'))
		cout << "Error reading sub area name acronym" << endl;

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
