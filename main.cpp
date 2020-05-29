/*
 * main.cpp
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */
// restarting ExoMatch
#include <cstdio>

//#include "BaseLinelist.h"
//#include "LinelistReader.h"
#include "Timer.h"
#include "ObsLinelist.h"
#include "CalcLinelist.h"
#include "Input.h"
#include "LinearAssigProb.h"
#include "CombinationDiffs.h"
//#include <Windows.h>
using namespace std;

int main(int argc, char* argv[]){

    std::string cmd_input = argv[1];

    Timer::getInstance().StartTimer("execute ExoMatch");

    Input user_input;
    Input *user_input_ptr = &user_input;

    user_input.SetInFileName(cmd_input);
    user_input.ReadInput();
    user_input.printInput();

    ObsLinelist obs_linelist(user_input_ptr);
    ObsLinelist *obs_linelist_ptr = &obs_linelist;
    CalcLinelist calc_linelist(user_input_ptr);
    CalcLinelist *calc_linelist_ptr = &calc_linelist;

    obs_linelist.initialize();

    calc_linelist.initialize();

    LinearAssigProb LAP(user_input_ptr,obs_linelist_ptr,calc_linelist_ptr);
    LinearAssigProb *LAP_ptr = &LAP;

    CombinationDiffs comb_diffs(user_input_ptr,obs_linelist_ptr,calc_linelist_ptr);


    int N_iter = user_input.GetMaxIter();
    bool perform_gscds_tf = user_input.GetPerformGSCDsTF();
    bool read_matches_tf = user_input.GetReadMatchesTF();

    // Here we start the big loop
    for(int iter = 0; iter < N_iter; iter++){

        if( iter==0 && read_matches_tf){
            LAP.readMatching(user_input.GetMatchesFileName());
        }else{
            LAP.Hungarian();
        }


        LAP.printMatching(user_input_ptr,obs_linelist_ptr,calc_linelist_ptr);


        if(!perform_gscds_tf) break;

        comb_diffs.setUp(LAP_ptr,obs_linelist_ptr);
        comb_diffs.findPartners(obs_linelist_ptr, calc_linelist_ptr, LAP_ptr);

        if(iter < N_iter-1)
            LAP.reset(comb_diffs.getAssignmentsObs2Calc(),comb_diffs.getAssignmentsCalc2Obs());

    }

    Timer::getInstance().EndTimer("execute ExoMatch");
    Timer::getInstance().printTimerData("execute ExoMatch");

    printf("\n End of program");

}

