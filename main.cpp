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
#include <Windows.h>
using namespace std;

int main(int argc, char* argv[]){

    std::string cmd_input = argv[1];
    std::cout << "cmd input is " << cmd_input << std::endl;

    Timer::getInstance().StartTimer("Read Input 4p1s");
    Sleep(1000);

    Timer::getInstance().StartTimer("ReadInput_100ms");
    Sleep(100);
    Timer::getInstance().EndTimer("ReadInput_100ms");
    Timer::getInstance().printTimerData("ReadInput_100ms");

    Timer::getInstance().StartTimer("ReadInput_3s");
    Sleep(3000);
    Timer::getInstance().EndTimer("ReadInput_3s");
    Timer::getInstance().printTimerData("ReadInput_3s");

    Timer::getInstance().EndTimer("Read Input 4p1s");
    Timer::getInstance().printTimerData("Read Input 4p1s");

    exit(0);
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

    // Here we start the big loop
    for(int i=0; i<N_iter; i++){

        LAP.Hungarian();
        LAP.printMatching(user_input_ptr,obs_linelist_ptr,calc_linelist_ptr);

        if(!perform_gscds_tf) break;

        comb_diffs.setUp(LAP_ptr,obs_linelist_ptr);
        comb_diffs.findPartners(obs_linelist_ptr, calc_linelist_ptr, LAP_ptr);

        LAP.clean();

    }


    printf("\n End of program");

}

