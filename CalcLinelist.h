/*
 * CalcLinelist.h
 *
 *  Created on: 8 Apr 2020
 *      Author: Phillip
 */

#ifndef CALCLINELIST_H_
#define CALCLINELIST_H_
#include "Utils.h"
#include "Input.h"
#include "BaseLinelist.h"
using namespace std;

class CalcLinelist : public BaseLinelist {
    private:
    int                    num_of_quanta;
    vector<double>         upper_energy;
    vector<double>         lower_energy;
    vector<vector<string>> upper_quanta;
    vector<vector<string>> lower_quanta;

    friend class LinearAssigProb;
    friend class CombinationDiffs;

    public:
    CalcLinelist(Input *pInput);//constructor
    ~CalcLinelist();//destructor
    void initialize();
    vector<vector<string>> GetUpperQuanta(){return upper_quanta;}
    vector<double>         GetUpperEnergy(){return upper_energy;}
    vector<vector<string>> GetLowerQuanta(){return lower_quanta;}
    vector<double>         GetLowerEnergy(){return lower_energy;}
};

#endif /* CALCLINELIST_H_ */
