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
    Input*         input;
    int            num_lines_in_file = 0;
    int            num_lines_in_match_set = 0;
    string         ll_file_name;
    vector<int>    global_assignment_map;
    vector<int>    matching;
    vector<int>    match_set_index_2_global_index;
    vector<double> cd_thresh;
    vector<double> wn;
    vector<double> intens;
    vector<double> matching_wn;
    vector<double> matching_intens;
    vector<string> spec_lines;

    int                  num_of_quanta;
    vector<double>       upper_energy;
    vector<double>       lower_energy;
    vector<vector<char>> upper_quanta;
    vector<vector<char>> lower_quanta;


    public:
    CalcLinelist();//constructor
    ~CalcLinelist();//destructor
    void initialize(Input *pInput);
    int            GetNumLinesInFile(){return num_lines_in_file;}
    vector<double> GetWn(){return wn;}
};

#endif /* CALCLINELIST_H_ */
