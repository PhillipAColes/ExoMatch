/*
 * ObsLinelist.cpp
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */
#include <memory>
#include <errno.h>
#include <cctype>
#include "Timer.h"
#include "Input.h"
#include "Utils.h"
#include "ObsLinelist.h"
using namespace std;

ObsLinelist::ObsLinelist(Input *pInput){

    ll_file_name = pInput->GetObsLLFileName();
    tmp_thresh_cd = pInput->GetCDThresh();

};

ObsLinelist::~ObsLinelist(){}

void ObsLinelist::initialize(){

    num_trans = 0;

    printf("\nProcessing %s...\n",ll_file_name.c_str());

    FILE * ll_file = fopen(ll_file_name.c_str(),"r");

    if (ll_file == NULL) perror ("Error opening file");

    char buffer[1024];

    while(fgets(buffer, 1024, ll_file)){
        num_trans++;
    }

    cout << "Number of lines to be read: " << num_trans << endl;

    rewind(ll_file);

    printf("Begin reading in experimental line list %s...",ll_file_name.c_str());

    Timer::getInstance().StartTimer("read obs linelist");

    int i_tmp = 0;

    while(fgets(buffer, 1024, ll_file)){

        vector<string> line_tmp;

         string line = (string)buffer;

         spec_lines.push_back(line);

         if(tmp_thresh_cd == 0){

             line_tmp = split_sub(trim(line),' ', 3);

             if( !isPositiveFloat(line_tmp[0].c_str())   ||
                 !isPositiveFloat(line_tmp[1].c_str())   ||
                 !isPositiveFloat(line_tmp[2].c_str())   ){
                     retLLError(i_tmp+1, ll_file_name);
             }

             pushLine(line_tmp,atof(line_tmp[2].c_str()));

         }else{

             line_tmp = split_sub(trim(line),' ', 2);

             if( !isPositiveFloat(line_tmp[0].c_str())   ||
                 !isPositiveFloat(line_tmp[1].c_str())   ){
                     retLLError(i_tmp+1, ll_file_name);
             }

             pushLine(line_tmp,tmp_thresh_cd);

         }

        i_tmp++;
    }

    printf(" done!\n");

    Timer::getInstance().EndTimer("read obs linelist");
    Timer::getInstance().printTimerData("read obs linelist");

    fclose(ll_file);

}

void ObsLinelist::pushLine(std::vector<std::string> & line, double line_cd_thresh){

    wn.push_back(atof(line[0].c_str()));

    intens.push_back(atof(line[1].c_str()));

    cd_thresh.push_back(line_cd_thresh);

}

