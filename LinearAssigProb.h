/*
 * LAP.h
 *
 *  Created on: 15 Apr 2020
 *      Author: Phillip
 *
 *  x_vert:          Set of obs lines (vertices) to be matched, each line consisting of [wavenumber,intensity]
 *  y_vert:          Set of calc lines (vertices) to be matched, each line consisting of [wavenumber,intensity]
 *  x_vert_idex:     The ith line (vertex) in x_vert corresponds to the x_vert_idex[i]th line in the full obs linelist
 *  y_vert_idex:     The jth line (vertex) in y_vert corresponds to the y_vert_idex[j]th line in the full calc linelist
 *  cost_coeff:      coefficient of wavenumber term in cost function
 */

#ifndef LINEARASSIGPROB_H_
#define LINEARASSIGPROB_H_

#include "Utils.h"
#include "ObsLinelist.h"
#include "CalcLinelist.h"
#include "Input.h"
using namespace std;

class LinearAssigProb{
private:
    vector<vector<double>> x_vert;
    vector<vector<double>> y_vert;
    int                    num_x_vert;
    int                    num_y_vert;
    int                    N_vert;
    vector<int>            x_vert_idex;
    vector<int>            y_vert_idex;
    int                    max_match;
    double                 cost_coeff;
    vector<vector<double>> cost; // cost matrix
    vector<double>         lx;
    vector<double>         ly;
    vector<int>            xy;
    vector<int>            yx;
    vector<bool>           S;
    vector<bool>           T;
    vector<double>         slack;
    vector<int>            slackx;
    vector<int>            previous;
    void generateCostMatrix();
    void initLabels();
    void updateLabels();
    void addToTree(int a, int b);
    void augment();

public:
    LinearAssigProb(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist);
    ~LinearAssigProb();
    void Hungarian();
    int GetNumXVert(){return num_x_vert;}
    int GetNumYVert(){return num_y_vert;}
    vector<int> GetXYMatching(){return xy;}
    vector<int> GetYXMatching(){return yx;}
    vector<vector<double>> GetXVert(){return x_vert;}
    vector<vector<double>> GetYVert(){return y_vert;}
    vector<int> GetXIdex(){return x_vert_idex;}
    vector<int> GetYIdex(){return y_vert_idex;}
    int cp = 80;

};

#endif /* LINEARASSIGPROB_H_ */
