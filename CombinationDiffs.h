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
    // from input
    double              intens_ratio;
    int                 min_num_cd_partners;

    // from LAP
    int                 num_obs_matches;
    vector<vector<int>> x2y;
    vector<vector<int>> xy_idex;

    // from obs linelist
//    int                 num_obs_trans;
//    vector<double>      obs_wn;
//    vector<double>      obs_intens;
//    vector<double>      cd_thresh;

    // from calc linelist
//    int                 num_calc_trans;
//    vector<double>      calc_wn;
//    vector<double>      calc_intens;
//    vector<double>      up_energy;
//    vector<double>      lw_energy;
    vector<string>      up_quanta_str;
    vector<string>      lw_quanta_str;

    // from combination diffs
    int                 num_assignments;
    vector<int>         assignments_obs2calc;
    vector<int>         assignments_calc2obs;


public:
    CombinationDiffs(Input *pInput, ObsLinelist *Obs, CalcLinelist *Calc);
    ~CombinationDiffs();
    void setUp(LinearAssigProb *pLAP, ObsLinelist *Obs);
    void findPartners(CalcLinelist *Calc, ObsLinelist *Obs, LinearAssigProb *pLAP);
};



#endif /* COMBINATIONDIFFS_H_ */
