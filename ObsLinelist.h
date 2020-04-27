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
    vector<string> spec_lines;

    double lw_range;
    double up_range;
    double int_thresh;
    double tmp_thresh_cd;
    vector<double> cd_thresh;

    void   checkObsInput(char*ln_buff,char*ln_ptr[],double ln_wn,double ln_intens, int ln_cdthr, int ln_num);

    public:
    ObsLinelist(Input *pInput);//constructor
    ~ObsLinelist();//destructor
    void initialize();

    int            GetNumTrans(){return num_trans;}
    vector<double> GetWn(){return wn;}
    vector<double> GetIntens(){return intens;}
    vector<double> GetCDThresh(){return cd_thresh;}
};

#endif /* OBSLINELIST_H_ */
