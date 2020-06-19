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

class LinearAssigProb{
private:
    std::vector<std::vector<double>> x_vert;
    std::vector<std::vector<double>> y_vert;
    int num_x_vert;
    int num_y_vert;
    int N_vert;
    std::vector<int> x_vert_idex;
    std::vector<int> y_vert_idex;
    int max_match;
    double cost_coeff;
    std::vector<std::vector<double>> cost; // cost matrix
    std::vector<double> lx;
    std::vector<double> ly;
    std::vector<int> xy;
    std::vector<int> yx;
    std::vector<std::vector<int>> x2y;
    std::vector<bool> S;
    std::vector<bool> T;
    std::vector<double> slack;
    std::vector<int> slackx;
    std::vector<int> previous;
    void generateCostMatrix();
    void initLabels();
    void updateLabels();
    void addToTree(int i_vert, int prev_i_vert);
    void augment();

public:
    LinearAssigProb(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist);
    ~LinearAssigProb();
    void Hungarian();
    void reset(std::vector<int> obs2calc, std::vector<int> calc2obs);
    void readMatching(std::string file_name);
    void printMatching(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist);
    int GetNumXVert(){return num_x_vert;}
    int GetNumYVert(){return num_y_vert;}
    std::vector<std::vector<int>> GetMatching(){return x2y;}
    std::vector<std::vector<double>> GetXVert(){return x_vert;}
    std::vector<std::vector<double>> GetYVert(){return y_vert;}
    std::vector<int> GetXIdex(){return x_vert_idex;}
    std::vector<int> GetYIdex(){return y_vert_idex;}

};

#endif /* LINEARASSIGPROB_H_ */
