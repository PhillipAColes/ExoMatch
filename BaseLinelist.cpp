/*
 * Linelist.cpp
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */
#include "BaseLinelist.h"

#include <string>
#include <iostream>
using namespace std;

void BaseLinelist::initialize(string fname){

    ll_file_name = fname;
    cout << "linelist file name: " << ll_file_name << endl;

}
