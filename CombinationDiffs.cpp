/*
 * CombinationDiffs.cpp
 *
 *  Created on: 17 Apr 2020
 *      Author: Phillip
 */

#include "CombinationDiffs.h"
#include <typeinfo>
using namespace std;

CombinationDiffs::CombinationDiffs(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist) : num_assignments(0){

    num_obs_trans = pObsLinelist->GetNumTrans();
    obs_wn = pObsLinelist->GetWn();
    obs_intens = pObsLinelist->GetIntens();
    cd_thresh = pObsLinelist->GetCDThresh();

    num_calc_trans = pCalcLinelist->GetNumTrans();
    calc_wn = pCalcLinelist->GetWn();
    calc_intens = pCalcLinelist->GetIntens();
    //calc_lines = &(pCalcLinelist->spec_lines);

    vector<vector<string>> up_quanta = pCalcLinelist->GetUpperQuanta();
    vector<vector<string>> lw_quanta = pCalcLinelist->GetLowerQuanta();

    up_quanta_str.resize(num_calc_trans);
    lw_quanta_str.resize(num_calc_trans);
    for (int i=0; i<num_calc_trans; i++) {
        for (string &up_q_label : up_quanta[i])up_quanta_str[i] += up_q_label;
        for (string &lw_q_label : lw_quanta[i])lw_quanta_str[i] += lw_q_label;
    }

    assignments_obs2calc.assign(num_obs_trans,-1);
    assignments_calc2obs.assign(num_calc_trans,-1);

};

CombinationDiffs::~CombinationDiffs(){}

void CombinationDiffs::setUp(LinearAssigProb *pLAP){

    num_obs_matches = pLAP->GetNumXVert();
    vector<int> x_idex = pLAP->GetXIdex();
    vector<int> y_idex = pLAP->GetYIdex();
    vector<int> xy = pLAP->GetXYMatching();


    // xy_idex[i][0] is the index of the ith matched obs line in the (complete) observed line list,
    // xy_idex[i][1] is the index of its matched partner in the (complete) calculated line list
    // i.e. line number xy_idex[i][0] in the obs line list has been matched to line number
    // xy_idex[i][1] in the calc line list.
    xy_idex.resize(num_obs_matches, vector<int> (2));
    for(int i=0; i<num_obs_matches; i++){
        xy_idex[i][0] = x_idex[i];
        xy_idex[i][1] = y_idex[xy[i]];
    }


    // sort xy_index by value of obs line intensity so that the strongest line is at index [0],
    // and the weakest line is at index [num_obs_matches-1]
    bool swapped;
    for (int i = 0; i < num_obs_matches-1; i++){
      swapped = false;
      for (int j = 0; j < num_obs_matches-i-1; j++) {
         if (obs_intens[xy_idex[j][0]] < obs_intens[xy_idex[j+1][0]]) {
             int tmp_x = xy_idex[j][0];
             int tmp_y = xy_idex[j][1];
             xy_idex[j][0] = xy_idex[j+1][0];
             xy_idex[j][1] = xy_idex[j+1][1];
             xy_idex[j+1][0] = tmp_x;
             xy_idex[j+1][1] = tmp_y;
            swapped = true;
         }
      }
      if (swapped == false) break;
    }

    for(int i=0;i<num_obs_matches;i++){
        cout << obs_wn[xy_idex[i][0]] << "  " << obs_intens[xy_idex[i][0]] << "  <--->  "
                << calc_wn[xy_idex[i][1]] << "  " << calc_intens[xy_idex[i][1]] << endl;
    }

}


void CombinationDiffs::findPartners(CalcLinelist *pCalcLinelist){


    for( int i=0; i<num_obs_matches; i++){

        int cd_count = 0;

        double energy_av = 0;

        int obs_match_idex = xy_idex[i][0];

        int calc_match_idex = xy_idex[i][1];

        double match_wn_diff = obs_wn[obs_match_idex] - calc_wn[calc_match_idex];

        double match_intens_ratio = obs_intens[obs_match_idex] / calc_intens[calc_match_idex];

//        cout << obs_wn[obs_match_idex] << "  " << obs_intens[obs_match_idex] << "  <--->  "
//                << calc_wn[calc_match_idex] << "  " << calc_intens[calc_match_idex] << endl;

        //if line already assigned then skip GSCDs
        if(assignments_obs2calc[obs_match_idex] == -1){
            cout << " ( " << obs_wn[obs_match_idex] << " , " << obs_intens[obs_match_idex] << " )   " <<
                    (pCalcLinelist->spec_lines)[calc_match_idex] << endl;
            continue;
        }

    }

}

