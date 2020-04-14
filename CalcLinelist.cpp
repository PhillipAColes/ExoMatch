/*
 * CalcLinelist.cpp
 *
 *  Created on: 8 Apr 2020
 *      Author: Phillip
 */

#include <memory>
#include <errno.h>
#include <cctype>
#include <stdio.h>
#include <string.h>
#include "Input.h"
#include "Utils.h"
#include "CalcLinelist.h"
using namespace std;
std::clock_t timestart,timeend,ticstaken,totaltimestart,totaltimeend;

//Constructor to initialise data members in class Input
CalcLinelist::CalcLinelist(Input *pInput) : linelist_type("calc"){

    ll_file_name = pInput->GetCalcLLFileName();
    num_of_quanta = pInput->GetNumOfQuanta();

};

CalcLinelist::~CalcLinelist(){}//destructor

void CalcLinelist::initialize(){

    num_trans = 0;

    FILE * ll_file = fopen(ll_file_name.c_str(),"r");

    char buffer[1024];
    size_t ll_size = 0;

    while(fgets(buffer, 1024, ll_file)){
        num_trans++;
        string s_tmp = (1,buffer);
        ll_size = ll_size + sizeof (trim(s_tmp));
    }
    printf("%zd bytes is required to hold linelist %s\n",ll_size,ll_file_name.c_str());

    cout << "Number of lines to be read from " << ll_file_name << " = " << num_trans << endl;

    rewind(ll_file);

    cout << "Begin reading in " << linelist_type << " linelist" << endl;

    timestart = std::clock();

    int i_tmp = 0;

    while(fgets(buffer, 1024, ll_file)){

        vector<string> line_tmp;

        string line = (string)buffer;

        line_tmp = split_sub(line,' ', 4+2*num_of_quanta);

        if( !isPositiveFloat(line_tmp[0].c_str())                 ||
            !isPositiveFloat(line_tmp[1].c_str())                 ||
            !isPositiveFloat(line_tmp[2+num_of_quanta].c_str())   ||
            !isPositiveFloat(line_tmp[2*num_of_quanta+3].c_str()) ){
                retLLError(i_tmp, ll_file_name);
        }

        wn.push_back(atof(line_tmp[0].c_str()));

        intens.push_back(atof(line_tmp[1].c_str()));

        vector<string> up_quanta_tmp = slice_vec(line_tmp,2,1+num_of_quanta);
        upper_quanta.push_back(up_quanta_tmp);

        upper_energy.push_back(atof(line_tmp[2+num_of_quanta].c_str()));

        vector<string> lw_quanta_tmp = slice_vec(line_tmp,3+num_of_quanta,2+2*num_of_quanta);
        lower_quanta.push_back(lw_quanta_tmp);

        lower_energy.push_back(atof(line_tmp[2*num_of_quanta+3].c_str()));

//        cout << wn[i_tmp] << " " << intens[i_tmp] << " " << upper_quanta[i_tmp][0] << " "
//                << upper_quanta[i_tmp][1] << " " << upper_quanta[i_tmp][2] << " "
//                << upper_energy[i_tmp] << " " << lower_quanta[i_tmp][0] << " "
//                << lower_quanta[i_tmp][1] << " " << lower_quanta[i_tmp][2] << " "
//                << lower_energy[i_tmp] << endl;
        i_tmp++;
    }

    timeend = std::clock();
    double duration = (timeend - timestart)/(double) CLOCKS_PER_SEC;

    cout << "... done" << endl;
    cout << "Time taken to read in calc file : " << duration << "seconds" << endl;

    fclose(ll_file);

    global_assignment_map.assign(num_trans,-1);

}

