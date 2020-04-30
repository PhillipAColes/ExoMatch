/*
 * BaseLinelist.h
 *
 *  Created on: 30 Apr 2020
 *      Author: Phillip
 */

#ifndef BASELINELIST_H_
#define BASELINELIST_H_

class BaseLinelist{
    protected:
    int            num_trans;
    string         ll_file_name;
    vector<double> wn;
    vector<double> intens;

    public:
    vector<string>         spec_lines;
    int                    GetNumTrans(){return num_trans;}
    vector<double>         GetWn(){return wn;}
    vector<double>         GetIntens(){return intens;}
};


#endif /* BASELINELIST_H_ */
