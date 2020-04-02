/*
 * Input.h
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Utils.h"
using namespace std;

class Input{
    private:
        string obs_ll_file_name;
        string calc_ll_file_name;
        string in_file_name;
        string matches_file_name;
        string print_match_info;
        double obs_range_lw;
        double obs_range_up;
        double calc_range_lw;
        double calc_range_up;
        double obs_int_thresh;
        double calc_int_thresh;
        double cost_coeff;
        double cd_thresh;
        double intens_ratio;
        int    gscd_set_size;
        int    num_quanta;
        int    max_iter;
        bool   perform_gscd_tf;
        bool   read_matches_tf;
        void checkInput(vector<string> vs);

    public:
        Input();//constructor
        ~Input();//destructor
        void   SetInFileName(string fname);
        void   ReadInput();
        string GetObsLLFileName(){return obs_ll_file_name;};
        string GetCalcLLFileName(){return calc_ll_file_name;};
        string GetPrintMatchInfo(){return print_match_info;};
        string GetMatchesFileName(){return matches_file_name;};
        double GetObsRangeLw(){return obs_range_lw;};
        double GetObsRangeUp(){return obs_range_up;};
        double GetCalcRangeLw(){return calc_range_lw;};
        double GetCalcRangeUp(){return calc_range_up;};
        double GetObsIntThresh(){return obs_int_thresh;};
        double GetCalcIntThresh(){return calc_int_thresh;};
        double GetCostCoeff(){return cost_coeff;};
        double GetCDThresh(){return cd_thresh;};
        double GetIntensRatio(){return intens_ratio;};
        int    GetGSCDSetSize(){return gscd_set_size;};
        int    GetNumOfQuanta(){return num_quanta;};
        int    GetMaxIter(){return max_iter;};
        bool   GetReadMatchesTF(){return read_matches_tf;};
        bool   GetPerformGSCDsTF(){return perform_gscd_tf;};
};

#endif /* INPUT_H_ */
