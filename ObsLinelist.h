/*
 * ObsLinelist.h
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */

#ifndef OBSLINELIST_H_
#define OBSLINELIST_H_
#include "Utils.h"
#include "Input.h"
using namespace std;

//class ObsLinelist : public BaseLinelist {
class ObsLinelist{
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

    public:
    ObsLinelist();//constructor
    ~ObsLinelist();//destructor
    void initialize(Input *pInput);
    int            GetNumLinesInFile(){return num_lines_in_file;}
    vector<double> GetWn(){return wn;}
};

#endif /* OBSLINELIST_H_ */
