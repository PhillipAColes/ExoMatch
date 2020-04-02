/*
 * main.cpp
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */
// restarting ExoMatch
#include <cstdio>
#include "Input.h"
using namespace std;

int main(int argc, char* argv[]){

    std::string cmd_input = argv[1];
    std::cout << "cmd input is " << cmd_input << std::endl;

    //user input is an instance of the Input class
    Input user_input;

    user_input.SetInFileName(cmd_input);
    user_input.ReadInput();

    cout << "obs_range_lw " << user_input.GetObsRangeLw() << std::endl;
    cout << "obs_range_up " << user_input.GetObsRangeUp() << std::endl;
    cout << "calc_range_lw " << user_input.GetCalcRangeLw() << std::endl;
    cout << "calc_range_up " << user_input.GetCalcRangeUp() << std::endl;
    cout << "obs_file is " << user_input.GetObsLLFileName() << std::endl;
    cout << "calc_file is " << user_input.GetCalcLLFileName() << std::endl;
    cout << "costcoeff is " << user_input.GetCostCoeff() << std::endl;
    cout << "CDthresh is " << user_input.GetCDThresh() << std::endl;
    cout << "Iratio " << user_input.GetIntensRatio() << std::endl;
    cout << "numGSCDs " << user_input.GetGSCDSetSize() << std::endl;
    cout << "Nquanta " << user_input.GetNumOfQuanta() << std::endl;
    cout << "maxiter " << user_input.GetMaxIter() << std::endl;
    cout << "readmatches " << user_input.GetMatchesFileName() << std::endl;
    cout << "matchinfo " << user_input.GetPrintMatchInfo() << std::endl;

}

