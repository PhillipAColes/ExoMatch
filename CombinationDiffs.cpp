/*
 * CombinationDiffs.cpp
 *
 *  Created on: 17 Apr 2020
 *      Author: Phillip
 */

#include "CombinationDiffs.h"
#include "Timer.h"
#include <typeinfo>
#include <math.h>
using namespace std;

CombinationDiffs::CombinationDiffs(Input *pInput, ObsLinelist *Obs, CalcLinelist *Calc) : num_assignments(0),
                                                                                          num_obs_matches(0){

    min_num_cd_partners = pInput->GetGSCDSetSize();
    intens_ratio =  pInput->GetIntensRatio();

    vector<vector<string>> up_quanta = Calc->GetUpperQuanta();
    vector<vector<string>> lw_quanta = Calc->GetLowerQuanta();

    up_quanta_str.resize(Calc->num_trans);
    lw_quanta_str.resize(Calc->num_trans);
    for (int i=0; i<Calc->num_trans; i++) {
        for (string &up_q_label : up_quanta[i])up_quanta_str[i] += up_q_label;
        for (string &lw_q_label : lw_quanta[i])lw_quanta_str[i] += lw_q_label;
    }

    assignments_obs2calc.assign(Obs->num_trans,-1);
    assignments_calc2obs.assign(Calc->num_trans,-1);

};

CombinationDiffs::~CombinationDiffs(){}

void CombinationDiffs::setUp(LinearAssigProb *pLAP, ObsLinelist *Obs){

    num_obs_matches = pLAP->GetNumXVert();
    x2y_srtd = pLAP->GetMatching();
    vector<int> x_idex = pLAP->GetXIdex();
    vector<int> y_idex = pLAP->GetYIdex();


    // xy_idex[i][0] is the index of the ith matched obs line in the (complete) observed line list,
    // xy_idex[i][1] is the index of its matched partner in the (complete) calculated line list
    // i.e. line number xy_idex[i][0] in the obs line list has been matched to line number
    // xy_idex[i][1] in the calc line list.
    xy_idex_srtd.resize(num_obs_matches, vector<int> (2));
    for(int i=0; i<num_obs_matches; i++){
        xy_idex_srtd[i][0] = x_idex[i];
        xy_idex_srtd[i][1] = y_idex[x2y_srtd[i][1]];
    }


    // sort xy_index by value of obs line intensity so that the strongest line is at index [0],
    // and the weakest line is at index [num_obs_matches-1]
    bool swapped;
    for (int i = 0; i < num_obs_matches-1; i++){
      swapped = false;
      for (int j = 0; j < num_obs_matches-i-1; j++) {
         if (Obs->intens[xy_idex_srtd[j][0]] < Obs->intens[xy_idex_srtd[j+1][0]]) {
             swap2d(&xy_idex_srtd[j],&xy_idex_srtd[j+1]);
             swap2d(&x2y_srtd[j],&x2y_srtd[j+1]);
            swapped = true;
         }
      }
      if (swapped == false) break;
    }


}


void CombinationDiffs::findPartners(ObsLinelist *Obs, CalcLinelist *Calc, LinearAssigProb *pLAP){


    Timer::getInstance().StartTimer("perform combination differences");
    printf("Performing ground state combination differences...");

    for( int i=0; i<num_obs_matches; i++){

        double energy_av = 0;

        int obs_match_idex = xy_idex_srtd[i][0];

        int calc_match_idex = xy_idex_srtd[i][1];

        double match_wn_diff = Obs->wn[obs_match_idex] - Calc->wn[calc_match_idex];

        double match_intens_ratio = Obs->intens[obs_match_idex] / Calc->intens[calc_match_idex];

        printf("[%-5d]   %12.6f  %13.8e     %12.6f  %13.8e   %12.6f \n", i,
                Obs->wn[obs_match_idex], Obs->intens[obs_match_idex],
                Calc->wn[calc_match_idex], Calc->intens[calc_match_idex], match_wn_diff);

        //if line already assigned then skip GSCDs
        if(assignments_obs2calc[obs_match_idex] > -1){
            cout << "           Already assigned to calc line:  " <<
                    (Calc->spec_lines)[assignments_obs2calc[obs_match_idex]] << endl;
            printf("\n");
            continue;
        }


        vector<int> tmp_gscd_partner;//index of calculated transition with same upper state as match

        #pragma omp parallel
        {
            vector<int> v_private;
            #pragma omp for nowait
            for (int j=0; j < Calc->num_trans; j++){
                if (up_quanta_str[j] == up_quanta_str[calc_match_idex] && Calc->upper_energy[j] == Calc->upper_energy[calc_match_idex]){
                    v_private.push_back(j);
                }
            }
            #pragma omp critical
            tmp_gscd_partner.insert(tmp_gscd_partner.end(), v_private.begin(), v_private.end());
        }

//        for (int j=0; j < Calc->num_trans; j++){
//            if (up_quanta_str[j] == up_quanta_str[calc_match_idex] && Calc->upper_energy[j] == Calc->upper_energy[calc_match_idex]){
//                tmp_gscd_partner.push_back(j);
//            }
//        }

        //index of (obs,calc) gscd pairs in a gscd set
        vector<vector<int>>  gscd_set_pairs(1, {obs_match_idex,calc_match_idex});

        // count number of gscd partners found
        int cd_count = 0;

        // look for gscd partners
        for (int j=0; j < Obs->num_trans; j++){
            for (int k=0; k < tmp_gscd_partner.size(); k++){
                if( (fabs(Obs->wn[j] - Calc->wn[tmp_gscd_partner[k]] - match_wn_diff) < Obs->cd_thresh[j])                     &&
                    (Obs->intens[j] / Calc->intens[tmp_gscd_partner[k]]) < match_intens_ratio*max(intens_ratio,1/intens_ratio) &&
                    (Obs->intens[j] / Calc->intens[tmp_gscd_partner[k]]) > match_intens_ratio/max(intens_ratio,1/intens_ratio) &&
                    assignments_obs2calc[j] == -1                                                                              &&
                    assignments_calc2obs[tmp_gscd_partner[k]] == -1                                                            &&
                    tmp_gscd_partner[k] != calc_match_idex                                                                     ){

                    gscd_set_pairs.push_back({j,tmp_gscd_partner[k]});
                    cd_count++;
                }
            }
        }


        if(cd_count >= min_num_cd_partners){
            for(int j=0; j<cd_count+1; j++){
                assignments_obs2calc[gscd_set_pairs[j][0]] = gscd_set_pairs[j][1];
                assignments_calc2obs[gscd_set_pairs[j][1]] = gscd_set_pairs[j][0];
                printf("          %12.6f  %13.8e     %12.6f  %13.8e   %12.6f \n",
                        Obs->wn[gscd_set_pairs[j][0]], Obs->intens[gscd_set_pairs[j][0]],
                        Calc->wn[gscd_set_pairs[j][1]] , Calc->intens[gscd_set_pairs[j][1]],
                        Obs->wn[gscd_set_pairs[j][0]] - Calc->wn[gscd_set_pairs[j][1]]);
            }
        }

        printf("\n");


    }

    Timer::getInstance().EndTimer("perform combination differences");
    Timer::getInstance().printTimerData("perform combination differences");

}


