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
    Input*      input;
    int         num_lines_in_file;
    int         num_lines_in_match_set;
    string      ll_file_name;
    vector<int> global_assignment_map;
    vector<int> matching;
    vector<int> match_set_index_2_global_index;

    public:
    ObsLinelist();//constructor
    ~ObsLinelist();//destructor
    void initialize(Input* pInput);
};

#endif /* OBSLINELIST_H_ */
