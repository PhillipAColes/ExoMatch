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
#include "BaseLinelist.h"
using namespace std;

class ObsLinelist : public BaseLinelist {
    private:
    double tmp_thresh_cd;
    vector<double> cd_thresh;

    friend class LinearAssigProb;
    friend class CombinationDiffs;

    public:
    ObsLinelist(Input *pInput);//constructor
    ~ObsLinelist();//destructor
    void initialize();
    vector<double> GetCDThresh(){return cd_thresh;}
};

#endif /* OBSLINELIST_H_ */
