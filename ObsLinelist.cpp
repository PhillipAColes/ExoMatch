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
ObsLinelist::ObsLinelist(){}

ObsLinelist::~ObsLinelist(){}//destructor

void ObsLinelist::initialize(Input *pInput){

    ll_file_name = pInput->GetObsLLFileName();

    double lw_obs_range = pInput->GetObsRangeLw();

    double up_obs_range = pInput->GetObsRangeUp();

    double obs_int_thresh = pInput->GetObsIntThresh();

    double thresh_cd = pInput->GetCDThresh();

    std::ifstream infile(ll_file_name.c_str());

    if(infile.fail()){
        cout << "Error: " << ll_file_name << " not found. Stopping." << endl;
        exit(0);
    }

    string ll_file_line;

    int i = 0, j = 0;

    while(getline(infile,ll_file_line)){

        spec_lines.push_back(trim(ll_file_line));

        // Split input line into fields
        vector<string> split_line = split(ll_file_line);

        // Check each line is valid input

        // Build vector of observed trans wavenumbers and intensities
        obs_wn.push_back(atof(split_line[0].c_str()));

        obs_intens.push_back(atof(split_line[1].c_str()));

        global_assignment_map.push_back(-1);

        if( obs_wn[i] > lw_obs_range && obs_wn[i] < up_obs_range && obs_intens[i] > obs_int_thresh){

            obs_matching_wn.push_back(obs_wn[i]);

            obs_matching_intens.push_back(obs_intens[i]);

            match_set_index_2_global_index.push_back(i);

            matching.push_back(-1);

            j++;

        }

        i++;

    }

    num_lines_in_file = i;

    num_lines_in_match_set = j;

    infile.close();

    if(num_lines_in_file==0){printf ("Error, file empty");exit (EXIT_FAILURE);}

}

