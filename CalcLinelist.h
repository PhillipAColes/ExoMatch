/*
 * CalcLinelist.h
 *
 *  Created on: 8 Apr 2020
 *      Author: Phillip
 */

#ifndef CALCLINELIST_H_
#define CALCLINELIST_H_
#include "Utils.h"
#include "Input.h"
using namespace std;

class CalcLinelist{
    private:
    int            num_trans;
    string         ll_file_name;
    string         linelist_type;
    vector<double> wn;
    vector<double> intens;

    int                  num_of_quanta;
    vector<double>       upper_energy;
    vector<double>       lower_energy;
    vector<vector<string>> upper_quanta;
    vector<vector<string>> lower_quanta;

    public:
    CalcLinelist(Input *pInput);//constructor
    ~CalcLinelist();//destructor
    void initialize();
    vector<string>         spec_lines;
    int                    GetNumTrans(){return num_trans;}
    vector<double>         GetWn(){return wn;}
    vector<double>         GetIntens(){return intens;}
    vector<vector<string>> GetUpperQuanta(){return upper_quanta;}
    vector<double>         GetUpperEnergy(){return upper_energy;}
    vector<vector<string>> GetLowerQuanta(){return lower_quanta;}
    vector<double>         GetLowerEnergy(){return lower_energy;}
};

#endif /* CALCLINELIST_H_ */
