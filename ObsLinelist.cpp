/*
 * ObsLinelist.cpp
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */
#include <memory>
#include <errno.h>
#include <cctype>
#include "Input.h"
#include "Utils.h"
#include "ObsLinelist.h"
using namespace std;

ObsLinelist::ObsLinelist(Input *pInput) : linelist_type("obs"){

    ll_file_name = pInput->GetObsLLFileName();
    tmp_thresh_cd = pInput->GetCDThresh();

};

ObsLinelist::~ObsLinelist(){}

void ObsLinelist::initialize(){

    num_trans = 0;

    FILE * ll_file = fopen(ll_file_name.c_str(),"r");

    char buffer[1024];

    while(fgets(buffer, 1024, ll_file)){
        num_trans++;
    }

    cout << "Number of lines to be read from " << ll_file_name << " = " << num_trans << endl;

    rewind(ll_file);

    cout << "Begin reading in " << linelist_type << " linelist" << endl;

    char * ln_ptr[3];
    int tmp_i = 0;
    double wn_tmp = 0;
    double intens_tmp = 0;
    double cd_tmp = 0;

    while(fgets(buffer, 1024, ll_file)){

        wn_tmp = strtod(buffer,&ln_ptr[0]);

        intens_tmp = strtod(ln_ptr[0],&ln_ptr[1]);

        if(tmp_thresh_cd == 0){
            cd_tmp = strtod(ln_ptr[1],&ln_ptr[2]);
        }else{
            cd_tmp = tmp_thresh_cd;
            ln_ptr[2] = ln_ptr[0];
        }

        checkObsInput(buffer,ln_ptr,wn_tmp,intens_tmp,cd_tmp,tmp_i);

        wn.push_back(wn_tmp);

        intens.push_back(intens_tmp);

        cd_thresh.push_back(cd_tmp);

        tmp_i++;
    }

    cout << "... done" << endl;

    fclose(ll_file);

    global_assignment_map.assign(num_trans,-1);

}



void ObsLinelist::checkObsInput(char*ln_buff,char*ln_ptr[],double ln_wn, double ln_intens, int ln_cdthr, int ln_num){

    errno = 0;

    if( ln_wn == 0     && (errno != 0 || ln_ptr[0] == ln_buff)   || !isspace(*ln_ptr[0]) ||
        ln_intens == 0 && (errno != 0 || ln_ptr[1] == ln_ptr[0]) || !isspace(*ln_ptr[1]) ||
        ln_cdthr == 0  && (errno != 0 || ln_ptr[2] == ln_ptr[1]) || !isspace(*ln_ptr[2]) ){

        fprintf(stderr, "Error line %d : input is not a valid double\n", ln_num+1);

        exit(EXIT_FAILURE);
    }

}

