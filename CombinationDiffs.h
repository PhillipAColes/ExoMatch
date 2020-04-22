/*
 * CombinationDiffs.h
 *
 *  Created on: 17 Apr 2020
 *      Author: Phillip
 */

#ifndef COMBINATIONDIFFS_H_
#define COMBINATIONDIFFS_H_

#include "LinearAssigProb.h"
#include "ObsLinelist.h"
#include "CalcLinelist.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>

class CombinationDiffs{
private:
    int num_assignments;
    vector<int> assignments_obs2calc;
    vector<int> assignments_calc2obs;
    vector<vector<int>> xy_idex;
    int min_cd_set_size;

    int num_obs_matches;
    int num_obs_trans;
    vector<double> obs_wn;
    vector<double> obs_intens;
    vector<double> cd_thresh;
    double intens_ratio;

    int num_calc_trans;
    vector<double> calc_wn;
    vector<double> calc_intens;
    vector<double> up_energy;
    vector<double> lw_energy;
    vector<string> up_quanta_str;
    vector<string> lw_quanta_str;
    //vector<string> * calc_lines;
    string calc_line;

public:
    CombinationDiffs(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist);
    ~CombinationDiffs();
    void setUp(LinearAssigProb *pLAP);
    void findPartners(CalcLinelist *pCalcLinelist);
};



#endif /* COMBINATIONDIFFS_H_ */
