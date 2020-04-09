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
ObsLinelist::ObsLinelist(Input *pInput) : linelist_type("obs"),
                                          num_lines_in_file(0),
                                          num_lines_in_match_set(0){

    ll_file_name = pInput->GetObsLLFileName();
    lw_range = pInput->GetObsRangeLw();
    up_range = pInput->GetObsRangeUp();
    int_thresh = pInput->GetObsIntThresh();
    thresh_cd = pInput->GetCDThresh();

};

ObsLinelist::~ObsLinelist(){}//destructor

void ObsLinelist::initialize(){

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
        if( split_line.size()==0 || !isPositiveFloat(split_line[0].c_str()) ||
            !isPositiveFloat(split_line[1].c_str())                         ||
            ( thresh_cd == 0 && !isPositiveFloat(split_line[2].c_str()) )   ){
            cout << "Error in " << ll_file_name << ", bad input at line number " << i+1 << endl;
            exit(0);
        }

        // Build vector of observed trans wavenumbers and intensities
        wn.push_back(atof(split_line[0].c_str()));

        intens.push_back(atof(split_line[1].c_str()));

        if(thresh_cd == 0){
            cd_thresh.push_back(atof(split_line[2].c_str()));
        } else {
            cd_thresh.push_back(thresh_cd);
        }

        global_assignment_map.push_back(-1);

        if( wn[i] > lw_range && wn[i] < up_range && intens[i] > int_thresh){

            matching_wn.push_back(wn[i]);

            matching_intens.push_back(intens[i]);

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

    cout << "Linelist is of type " << linelist_type << endl;

}

