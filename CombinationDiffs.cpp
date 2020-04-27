/*
 * CombinationDiffs.cpp
 *
 *  Created on: 17 Apr 2020
 *      Author: Phillip
 */

#include "CombinationDiffs.h"
#include <typeinfo>
#include <math.h>
using namespace std;

CombinationDiffs::CombinationDiffs(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist) : num_assignments(0),
                                                                                                            num_obs_matches(0){

    min_num_cd_partners = pInput->GetGSCDSetSize();
    intens_ratio =  pInput->GetIntensRatio();

    num_obs_trans = pObsLinelist->GetNumTrans();
    obs_wn = pObsLinelist->GetWn();
    obs_intens = pObsLinelist->GetIntens();
    cd_thresh = pObsLinelist->GetCDThresh();

    num_calc_trans = pCalcLinelist->GetNumTrans();
    calc_wn = pCalcLinelist->GetWn();
    calc_intens = pCalcLinelist->GetIntens();
    up_energy = pCalcLinelist->GetUpperEnergy();
    lw_energy = pCalcLinelist->GetLowerEnergy();

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
    x2y = pLAP->GetMatching();
    vector<int> x_idex = pLAP->GetXIdex();
    vector<int> y_idex = pLAP->GetYIdex();


    // xy_idex[i][0] is the index of the ith matched obs line in the (complete) observed line list,
    // xy_idex[i][1] is the index of its matched partner in the (complete) calculated line list
    // i.e. line number xy_idex[i][0] in the obs line list has been matched to line number
    // xy_idex[i][1] in the calc line list.
    xy_idex.resize(num_obs_matches, vector<int> (2));
    for(int i=0; i<num_obs_matches; i++){
        xy_idex[i][0] = x_idex[i];
        xy_idex[i][1] = y_idex[x2y[i][1]];
    }


    // sort xy_index by value of obs line intensity so that the strongest line is at index [0],
    // and the weakest line is at index [num_obs_matches-1]
    bool swapped;
    for (int i = 0; i < num_obs_matches-1; i++){
      swapped = false;
      for (int j = 0; j < num_obs_matches-i-1; j++) {
         if (obs_intens[xy_idex[j][0]] < obs_intens[xy_idex[j+1][0]]) {
             swap2d(&xy_idex[j],&xy_idex[j+1]);
             swap2d(&x2y[j],&x2y[j+1]);
//             int tmp_x = xy_idex[j][0];
//             int tmp_y = xy_idex[j][1];
//             xy_idex[j][0] = xy_idex[j+1][0];
//             xy_idex[j][1] = xy_idex[j+1][1];
//             xy_idex[j+1][0] = tmp_x;
//             xy_idex[j+1][1] = tmp_y;
            swapped = true;
         }
      }
      if (swapped == false) break;
    }


}


void CombinationDiffs::findPartners(CalcLinelist *pCalcLinelist, ObsLinelist *pObsLinelist, LinearAssigProb *pLAP){


    for( int i=0; i<num_obs_matches; i++){

        double energy_av = 0;

        int obs_match_idex = xy_idex[i][0];

        int calc_match_idex = xy_idex[i][1];

        double match_wn_diff = obs_wn[obs_match_idex] - calc_wn[calc_match_idex];

        double match_intens_ratio = obs_intens[obs_match_idex] / calc_intens[calc_match_idex];

        printf("[%-5d]   %12.6f  %13.8e     %12.6f  %13.8e   %12.6f \n", i,
                obs_wn[obs_match_idex], obs_intens[obs_match_idex],
                calc_wn[calc_match_idex], calc_intens[calc_match_idex], match_wn_diff);

        //if line already assigned then skip GSCDs
        if(assignments_obs2calc[obs_match_idex] > -1){
            cout << " Already assigned to calc line   " <<
                    (pCalcLinelist->spec_lines)[assignments_obs2calc[obs_match_idex]] << endl;
           // printf("Already assigned to calc line   %s \n",&(pCalcLinelist->spec_lines)[calc_match_idex]);
            printf("\n");
            continue;
        }


        vector<int> tmp_gscd_partner;//index of calculated transition with same upper state as match

        for (int j=0; j < num_calc_trans; j++){
            if (up_quanta_str[j] == up_quanta_str[calc_match_idex] && up_energy[j] == up_energy[calc_match_idex]){
                tmp_gscd_partner.push_back(j);
            }
        }

        //index of (obs,calc) gscd pairs in a gscd set
        vector<vector<int>>  gscd_set_pairs(1, {obs_match_idex,calc_match_idex});

        // count number of gscd partners found
        int cd_count = 0;

        // look for gscd partners
        for (int j=0; j < num_obs_trans; j++){
            for (int k=0; k < tmp_gscd_partner.size(); k++){
                if( (fabs(obs_wn[j] - calc_wn[tmp_gscd_partner[k]] - match_wn_diff) < cd_thresh[j])     &&
                    (obs_intens[j] / calc_intens[tmp_gscd_partner[k]]) < match_intens_ratio*max(intens_ratio,1/intens_ratio) &&
                    (obs_intens[j] / calc_intens[tmp_gscd_partner[k]]) > match_intens_ratio/max(intens_ratio,1/intens_ratio) &&
                    assignments_obs2calc[j] == -1                                                        &&
                    assignments_calc2obs[tmp_gscd_partner[k]] == -1                                      &&
                    tmp_gscd_partner[k] != calc_match_idex                                               ){

                    gscd_set_pairs.push_back({j,tmp_gscd_partner[k]});
                    cd_count++;
                }
            }
        }


        if(cd_count >= min_num_cd_partners){
            for(int j=0; j<cd_count+1; j++){
                assignments_obs2calc[gscd_set_pairs[j][0]] = gscd_set_pairs[j][1];
                assignments_calc2obs[gscd_set_pairs[j][1]] = gscd_set_pairs[j][0];
                printf("gscd pair:  %12.6f  %13.8e     %12.6f  %13.8e    %12.6f \n",
                        obs_wn[gscd_set_pairs[j][0]],obs_intens[gscd_set_pairs[j][0]],
                        calc_wn[gscd_set_pairs[j][1]] , calc_intens[gscd_set_pairs[j][1]],
                        obs_wn[gscd_set_pairs[j][0]]-calc_wn[gscd_set_pairs[j][1]]);
            }
            //remove assignments from future matching
            pLAP->removePair(x2y[i][0],x2y[i][1]);

        }

        printf("\n");


    }

}

