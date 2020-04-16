/*
 * Linelist.h
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */

#ifndef BASELINELIST_H_
#define BASELINELIST_H_

#include "Utils.h"
using namespace std;

class BaseLinelist{
//    private:

//    protected:
//        string         linelist_file_name;
//        int            num_lines_in_linelist;
//        int            num_lines_in_matching;
//        vector<int>    global_assignment_map; // maps index of obs/calc line to index of assigned calc/obs line
//        vector<int>    match_set_map;
//        vector<int>    matching_set_index_2_global_index;
//        vector<string> transitions;
//        int            countLinesInMatchingSet{}();
    protected:
        string         ll_file_name;

    public:
        Linelist(){};
        void           initialize(string fname);

};



#endif /* BASELINELIST_H_ */
