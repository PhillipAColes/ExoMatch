/*
 * ObsLinelist.cpp
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */
#include "Input.h"
#include "Utils.h"
#include "ObsLinelist.h"

//Constructor to initialise data members in class Input
ObsLinelist::ObsLinelist():num_lines_in_file(0),
                           num_lines_in_match_set(0){

};


ObsLinelist::~ObsLinelist(){}//destructor

void ObsLinelist::initialize(Input* pInput){

    ll_file_name = pInput->GetObsLLFileName();
    std::cout << "User input file is " << ll_file_name << std::endl;
}


