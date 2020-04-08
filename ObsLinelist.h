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
    vector<double> obs_wn;
    vector<double> obs_intens;
    vector<double> obs_matching_wn;
    vector<double> obs_matching_intens;
    vector<string> spec_lines;

    public:
    ObsLinelist();//constructor
    ~ObsLinelist();//destructor
    void initialize(Input *pInput);
};

#endif /* OBSLINELIST_H_ */
