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
    vector<vector<int>> x2y_srtd;
    vector<vector<int>> xy_idex_srtd;

    // from Calc linelist
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
    void findPartners(ObsLinelist *Obs, CalcLinelist *Calc);
    vector<int> getAssignmentsObs2Calc(){return assignments_obs2calc;};
    vector<int> getAssignmentsCalc2Obs(){return assignments_calc2obs;};
};



#endif /* COMBINATIONDIFFS_H_ */
