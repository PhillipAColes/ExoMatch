/*
 * ObsLinelist.h
 *
 *  Created on: 6 Apr 2020
 *      Author: Phillip
 */

#ifndef OBSLINELIST_H_
#define OBSLINELIST_H_
#include "Utils.h"
#include "Input.h"
using namespace std;

//class ObsLinelist : public BaseLinelist {
class ObsLinelist{
    private:
    int            num_trans;
    string         ll_file_name;
    string         linelist_type;
    vector<double> wn;
    vector<double> intens;

    double tmp_thresh_cd;
    vector<double> cd_thresh;

    friend class CombinationDiffs;

    public:
    ObsLinelist(Input *pInput);//constructor
    ~ObsLinelist();//destructor
    void initialize();
    vector<string> spec_lines;
    int            GetNumTrans(){return num_trans;}
    vector<double> GetWn(){return wn;}
    vector<double> GetIntens(){return intens;}
    vector<double> GetCDThresh(){return cd_thresh;}
};

#endif /* OBSLINELIST_H_ */
