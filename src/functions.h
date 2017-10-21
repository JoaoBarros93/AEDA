#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "user.h"


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void Login(int n,vector<User> &users);
bool Register(vector<User> &users);
void Menu1(vector<User> &users);
void Menu2(User user,vector<User> &users);






#endif
