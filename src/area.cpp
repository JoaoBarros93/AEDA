#include "area.h"

Area::Area(){
}

Area::Area(stringstream& s) {
	stringstream ss;
	string newAreaName, newSubAreaName, newAreaNameSigla, newSubAreaNameSigla;

	if (!getline(s, newAreaName, ';'))
		cout << "Error getting area name" << endl;

	ss << newAreaName;
	ss >> areaName;
	ss.clear();
	this->areaName = areaName;

	if (!getline(s, newSubAreaName, ';'))
		cout << "Error getting subarea name" << endl;

	ss << newSubAreaName;
	ss >> subAreaName;
	ss.clear();
	this->subAreaName = subAreaName;

	if (!getline(s, newAreaNameSigla, ';'))
		cout << "Error getting area name sigla" << endl;

	ss << newAreaNameSigla;
	ss >> areaNameSigla;
	ss.clear();
	this->areaNameSigla = areaNameSigla;

	if (!getline(s, newSubAreaNameSigla, ';'))
		cout << "Error getting sub area name sigla" << endl;

	ss << newSubAreaNameSigla;
	ss >> subAreaNameSigla;
	ss.clear();
	this->subAreaNameSigla = subAreaNameSigla;
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
