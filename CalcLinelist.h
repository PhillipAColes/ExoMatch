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
//    Input*         input;
    int            num_trans;
//    int            num_lines_in_match_set;
    string         ll_file_name;
    string         linelist_type;
    vector<int>    global_assignment_map; // the ith calc line is assigned to the global_assignment_map[i]th obs line
//    vector<int>    matching;
//    vector<int>    match_set_index_2_global_index;
    vector<double> wn;
    vector<double> intens;
//    vector<double> matching_wn;
//    vector<double> matching_intens;
    vector<string> spec_lines;

    int                  num_of_quanta;
    vector<double>       upper_energy;
    vector<double>       lower_energy;
    vector<vector<string>> upper_quanta;
    vector<vector<string>> lower_quanta;

    public:
    CalcLinelist(Input *pInput);//constructor
    ~CalcLinelist();//destructor
    void initialize();
    int                    GetNumLinesInFile(){return num_trans;}
    vector<double>         GetWn(){return wn;}
    vector<double>         GetIntens(){return intens;}
    vector<vector<string>> GetUpperQuanta(){return upper_quanta;}
    vector<double>         GetUpperEnergy(){return upper_energy;}
    vector<vector<string>> GetLowerQuanta(){return lower_quanta;}
    vector<double>         GetLowerEnergy(){return lower_energy;}
};

#endif /* CALCLINELIST_H_ */
