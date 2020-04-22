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
#include "ObsLinelist.h"
#include "CalcLinelist.h"
#include "Input.h"
#include "LinearAssigProb.h"
#include "CombinationDiffs.h"
using namespace std;

int main(int argc, char* argv[]){

    std::string cmd_input = argv[1];
    std::cout << "cmd input is " << cmd_input << std::endl;

    Input user_input;
    Input *user_input_ptr = &user_input;

    user_input.SetInFileName(cmd_input);
    user_input.ReadInput();

    cout << "obs_range_lw " << user_input.GetObsRangeLw() << std::endl;
    cout << "obs_range_up " << user_input.GetObsRangeUp() << std::endl;
    cout << "obs_int_thresh " << user_input.GetObsIntThresh() << std::endl;
    cout << "calc_range_lw " << user_input.GetCalcRangeLw() << std::endl;
    cout << "calc_range_up " << user_input.GetCalcRangeUp() << std::endl;
    cout << "calc_int_thresh " << user_input.GetCalcIntThresh() << std::endl;
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

    ObsLinelist obs_linelist(user_input_ptr);
    obs_linelist.initialize();
    ObsLinelist *obs_linelist_ptr = &obs_linelist;

    CalcLinelist calc_linelist(user_input_ptr);
    calc_linelist.initialize();
    CalcLinelist *calc_linelist_ptr = &calc_linelist;

//    int num_lines = obs_linelist.GetNumLinesInFile();
//
//    vector<double> wavenumber = obs_linelist.GetWn();
//    vector<double> intens = obs_linelist.GetIntens();
//    vector<double> cds = obs_linelist.GetCDThresh();
//
//    for(int i=0; i<num_lines; i++){
//        cout << wavenumber[i] << "  " << intens[i] << "  " << cds[i] << endl;
//    }
//
//    num_lines = calc_linelist.GetNumLinesInFile();
//
//    vector<double> cwavenumber = calc_linelist.GetWn();
//    vector<double> cintens = calc_linelist.GetIntens();
//
//    for(int i=0; i<num_lines; i++){
//        cout << cwavenumber[i] << "  " << cintens[i] << "  " << endl;
//    }

    LinearAssigProb LAP(user_input_ptr,obs_linelist_ptr,calc_linelist_ptr);
    LinearAssigProb *LAP_ptr = &LAP;
    LAP.Hungarian();


    CombinationDiffs comb_diffs(user_input_ptr,obs_linelist_ptr,calc_linelist_ptr);
    comb_diffs.setUp(LAP_ptr);
    comb_diffs.findPartners(calc_linelist_ptr);

}

