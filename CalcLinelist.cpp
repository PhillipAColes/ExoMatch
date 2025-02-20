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
#include "Timer.h"
#include "CalcLinelist.h"
using namespace std;

CalcLinelist::CalcLinelist(Input *pInput){

    ll_file_name = pInput->GetCalcLLFileName();
    num_of_quanta = pInput->GetNumOfQuanta();

};

CalcLinelist::~CalcLinelist(){}

void CalcLinelist::initialize(){

    num_trans = 0;

    printf("\nProcessing %s...\n",ll_file_name.c_str());

    FILE * ll_file = fopen(ll_file_name.c_str(),"r");

    if (ll_file == NULL) perror ("Error opening file");

    char buffer[1024];
    size_t ll_size = 0;

    while(fgets(buffer, 1024, ll_file)){
        num_trans++;
        string s_tmp = (buffer);
        ll_size = ll_size + sizeof (trim(s_tmp));
    }
    printf("%zd bytes is required to hold linelist %s\n",ll_size,ll_file_name.c_str());

    cout << "Number of lines to be read = " << num_trans << endl;

    rewind(ll_file);

    printf("Begin reading theoretical line list %s...",ll_file_name.c_str());

    Timer::getInstance().StartTimer("read calc linelist");

    int i_tmp = 0;

    while(fgets(buffer, 1024, ll_file)){

        vector<string> line_tmp;

        string line = (string)buffer;

        spec_lines.push_back(line);

        line_tmp = split_sub(trim(line),' ', 4+2*num_of_quanta);

        if( !isPositiveFloat(line_tmp[0].c_str())                 ||
            !isPositiveFloat(line_tmp[1].c_str())                 ||
            !isPositiveFloat(line_tmp[2+num_of_quanta].c_str())   ||
            !isPositiveFloat(line_tmp[(2*num_of_quanta)+3].c_str()) ){
                retLLError(i_tmp+1, ll_file_name);
        }

        pushLine(line_tmp);

        i_tmp++;
    }

    printf(" done!\n");

    Timer::getInstance().EndTimer("read calc linelist");
    Timer::getInstance().printTimerData("read calc linelist");

    fclose(ll_file);

}

void CalcLinelist::pushLine(std::vector<std::string> & line){

    wn.push_back(atof(line[0].c_str()));

    intens.push_back(atof(line[1].c_str()));

    vector<string> up_quanta_tmp = slice_vec(line,2,1+num_of_quanta);
    upper_quanta.push_back(up_quanta_tmp);

    upper_energy.push_back(atof(line[2+num_of_quanta].c_str()));

    vector<string> lw_quanta_tmp = slice_vec(line,3+num_of_quanta,2+2*num_of_quanta);
    lower_quanta.push_back(lw_quanta_tmp);

    lower_energy.push_back(atof(line[2*num_of_quanta+3].c_str()));

}

