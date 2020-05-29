/*
 * LAP.cpp
 *
 *  Created on: 15 Apr 2020
 *      Author: Phillip
 */

#include "LinearAssigProb.h"
#include "Utils.h"
#include "Timer.h"
#include <math.h>
#include <iomanip>
#include <utility>
using namespace std;
#define INF 100000000

LinearAssigProb::LinearAssigProb(Input *pInput, ObsLinelist *Obs, CalcLinelist *Calc) : num_x_vert(0),
                                                                                  num_y_vert(0),
                                                                                  N_vert(0),
                                                                                  max_match(0),
                                                                                  cost_coeff(pInput->GetCostCoeff()){

    double obs_range_lw = pInput->GetObsRangeLw();
    double obs_range_up = pInput->GetObsRangeUp();
    double calc_range_lw = pInput->GetCalcRangeLw();
    double calc_range_up = pInput->GetCalcRangeUp();
    double obs_int_thresh = pInput->GetObsIntThresh();
    double calc_int_thresh = pInput->GetCalcIntThresh();

    printf("Initializing matching sets...\n");

    for ( int i = 0 ; i < Obs->num_trans; i++ ){
        if (Obs->wn[i] > obs_range_lw && Obs->wn[i] < obs_range_up && Obs->intens[i] > obs_int_thresh){
            x_vert.push_back({Obs->wn[i],Obs->intens[i]});
            x_vert_idex.push_back(i);
            num_x_vert++;
        }
    }

    for ( int j = 0 ; j < Calc->num_trans; j++ ){
        if (Calc->wn[j] > calc_range_lw && Calc->wn[j] < calc_range_up && Calc->intens[j] > calc_int_thresh){
            y_vert.push_back({Calc->wn[j],Calc->intens[j]});
            y_vert_idex.push_back(j);
            num_y_vert++;
        }
    }

    printf("number of experimental lines in matching: %i\n",num_x_vert);
    printf("number of theoretical lines in matching: %i\n",num_y_vert);


    N_vert = num_y_vert;

};

LinearAssigProb::~LinearAssigProb(){}


void LinearAssigProb::generateCostMatrix(){

    double maxcost = 0;

    cost.resize(num_y_vert,vector<double>(num_y_vert));

    printf("Coefficient of intensity contribution to cost matrix = %6.3f\n",cost_coeff);
    printf("Generating cost matrix...\n");

    Timer::getInstance().StartTimer("generate cost matrix");

    // fill in cost matrix
    for(int i = 0; i < num_x_vert; i++){
        for(int j = 0; j < num_y_vert; j++){
            double nudiff = fabs(x_vert[i][0] - y_vert[j][0]);
            double intdiff = cost_coeff * fabs(log(x_vert[i][1]/y_vert[j][1]));
            cost[i][j] = sqrt( nudiff*nudiff + intdiff*intdiff);
            maxcost=max(maxcost,cost[i][j]);
        }
    }

    // convert problem to one of maximising cost
    for(int i = 0; i < num_x_vert; i++){
        for(int j = 0; j < num_y_vert; j++){
            cost[i][j]=maxcost-cost[i][j];
        }
    }

    // zero padding to make cost matrix square
    for(int i = num_x_vert; i < num_y_vert; i++){
        for(int j = 0; j < num_y_vert; j++){
            cost[i][j]=0.0;
        }
    }

    cout << "... done\n" << endl;

    Timer::getInstance().EndTimer("generate cost matrix");
    Timer::getInstance().printTimerData("generate cost matrix");

}


void LinearAssigProb::Hungarian(){

    x2y.resize(num_x_vert);
    xy.resize(N_vert);
    yx.resize(N_vert);
    S.resize(N_vert);
    T.resize(N_vert);
    slack.resize(N_vert);
    slackx.resize(N_vert);
    previous.resize(N_vert);

    generateCostMatrix();

    Timer::getInstance().StartTimer("match line lists");

    printf("Performing optimal matching...\n");

    initLabels();

    xy.assign(N_vert,-1);
    yx.assign(N_vert,-1);

    max_match = 0;

    while (max_match<N_vert){
        augment();
    }

    printf("...done\n");

    Timer::getInstance().EndTimer("match line lists");
    Timer::getInstance().printTimerData("match line lists");


    for (int x = 0; x < num_x_vert; x++)
        x2y[x] = {x,xy[x]};

}

void LinearAssigProb::initLabels(){

    lx.resize(N_vert);
    ly.resize(N_vert);
    lx.assign(N_vert,0);
    ly.assign(N_vert,0);

    for (int i_vert = 0; i_vert < N_vert; i_vert++){
        for (int j_vert = 0; j_vert < N_vert; j_vert++){
            lx[i_vert] = max(lx[i_vert], cost[i_vert][j_vert]);
        }
    }

}


void LinearAssigProb::updateLabels(){

    int i_vert,j_vert;
    double delta = INF; //init delta as infinity

    for (j_vert = 0; j_vert < N_vert; j_vert++){ //calculate delta using slack
        if (!T[j_vert]) delta = min(delta, slack[j_vert]);
    }

    for (i_vert = 0; i_vert < N_vert; i_vert++){ //update X labels
        if (S[i_vert]) lx[i_vert] -= delta;
    }

    for (j_vert = 0; j_vert < N_vert; j_vert++){ //update Y labels
        if (T[j_vert]) ly[j_vert] += delta;
    }

    for (j_vert = 0; j_vert < N_vert; j_vert++){ //update slack array
        if (!T[j_vert]){
            slack[j_vert] -= delta;
        }
    }
}


void LinearAssigProb::addToTree(int i_vert, int prev_i_vert){
    S[i_vert] = true; //add x to S
    previous[i_vert] = prev_i_vert; //we need this when augmenting

    for (int j_vert = 0; j_vert < N_vert; j_vert++){                    //update slacks, because we add new vertex to S
        if (lx[i_vert] + ly[j_vert] - cost[i_vert][j_vert] < slack[j_vert]){
            slack[j_vert] = lx[i_vert] + ly[j_vert] - cost[i_vert][j_vert];  //minimum residual lx[x]+ly[y]-cost[x][y] for each y
            slackx[j_vert] = i_vert;                          //and x that minimum belongs to
        }
    }
}


void LinearAssigProb::augment(){ //main function of the algorithm

    if (max_match == N_vert) return; //check wether matching is already perfect
    int i_vert, j_vert, root; //just counters and root vertex
    int q[N_vert], wr = 0, rd = 0; //q - queue for bfs, wr,rd - write and read

    //pos in queue
    for (int k = 0; k < N_vert; k++){S[k]=false;T[k]=false;previous[k]=-1;}

    for (i_vert = 0; i_vert < N_vert; i_vert++){ //finding root of the tree
        if (xy[i_vert] == -1){
            q[wr++] = root = i_vert;
            previous[i_vert] = -2;
            S[i_vert] = true;
            break;
        }
    }


    for (j_vert = 0; j_vert < N_vert; j_vert++){ //initializing slack array
        slack[j_vert] = lx[root] + ly[j_vert] - cost[root][j_vert];
        slackx[j_vert] = root;
    }

    while (true){ //main cycle

        while (rd < wr){ //building tree with bfs cycle
            i_vert = q[rd++]; //current vertex from X part
            for (j_vert = 0; j_vert < N_vert; j_vert++){ //iterate through all edges in equality graph
                if (cost[i_vert][j_vert] == lx[i_vert] + ly[j_vert] && !T[j_vert]){//equality graph is defined by cost[x][y]==lx[x]+ly[y]
                    if (yx[j_vert] == -1) break; //an exposed vertex in Y found, so augmenting path exists!
                    T[j_vert] = true; //else just add y to T,
                    q[wr++] = yx[j_vert]; //add vertex yx[y], which is matched with y, to the queue
                    addToTree(yx[j_vert], i_vert); //add edges (x,y) and (y,yx[y]) to the tree
                }
            }
            if (j_vert < N_vert) break; //augmenting path found!
        }

        if (j_vert < N_vert) break; //augmenting path found!

        updateLabels(); //augmenting path not found, so improve labeling

        wr = rd = 0;

        for (j_vert = 0; j_vert < N_vert; j_vert++){
        //in this cycle we add edges that were added to the equality graph as a
        //result of improving the labeling, we add edge (slackx[y], y) to the tree if
        //and only if !T[y] && slack[y] == 0, also with this edge we add another one
        //(y, yx[y]) or augment the matching, if y was exposed
            if (!T[j_vert] && slack[j_vert] == 0){
                if (yx[j_vert] == -1){ //exposed vertex in Y found - augmenting path exists!
                    i_vert = slackx[j_vert];
                    break;
                }else{
                    T[j_vert] = true; //else just add y to T,
                    if (!S[yx[j_vert]]){
                        q[wr++] = yx[j_vert]; //add vertex yx[y], which is matched with y, to the queue
                        addToTree(yx[j_vert], slackx[j_vert]); //and add edges (x,y) and (y,yx[y]) to the tree
                    }
                }
            }
        }

        if (j_vert < N_vert) break; //augmenting path found!
    }

    if (j_vert < N_vert){ //we found augmenting path!
        max_match++; //increment matching
        for (int cx = i_vert, cy = j_vert, ty; cx != -2; cx = previous[cx], cy = ty){
            ty = xy[cx];
            yx[cy] = cx;
            xy[cx] = cy;
        }
    }
return;
}//end of augment() function


void LinearAssigProb::reset(vector<int> assignments_obs2calc, vector<int> assignments_calc2obs){

    printf("Resetting LAP...\n");

    vector<vector<double>> tmp_x_vert = std::move(x_vert);
    vector<vector<double>> tmp_y_vert = std::move(y_vert);
    vector<int>            tmp_x_vert_idex = std::move(x_vert_idex);
    vector<int>            tmp_y_vert_idex = std::move(y_vert_idex);

    num_x_vert = 0;
    num_y_vert = 0;
    N_vert = 0;

    for (int i = 0; i < tmp_x_vert.size() ; i++){
        if(assignments_obs2calc[tmp_x_vert_idex[i]] == -1){
            x_vert.push_back(tmp_x_vert[i]);
            x_vert_idex.push_back(tmp_x_vert_idex[i]);
            num_x_vert++;
        }
    }

    for (int j = 0; j < tmp_y_vert.size() ; j++){
        if(assignments_calc2obs[tmp_y_vert_idex[j]] == -1){
            y_vert.push_back(tmp_y_vert[j]);
            y_vert_idex.push_back(tmp_y_vert_idex[j]);
            num_y_vert++;
        }
    }

    cout << "Number of experimental lines in matching: " << num_x_vert << endl;
    cout << "Number of theoretical lines in matching: " << num_y_vert << endl;

    N_vert = num_y_vert;

    x2y.clear();
    xy.clear();
    yx.clear();
    S.clear();
    T.clear();
    slack.clear();
    slackx.clear();
    previous.clear();
    lx.clear();
    ly.clear();
    cost.clear();

}

void LinearAssigProb::readMatching(string matching_file_name){

    printf("Matching to be read from file %s\n",matching_file_name.c_str());

    std::ifstream infile(matching_file_name.c_str());

    if(infile.fail()){
        printf("Error: %s not found. Stopping.",matching_file_name);
        exit(0);
    }

    string match_file_line;

    int i_tmp = 0;

    while(getline(infile,match_file_line)){
        match_file_line = trim(match_file_line);
        vector<string> split_line = split(match_file_line);
        if( !isPositiveInt(split_line[0].c_str()) || !isPositiveInt(split_line[1].c_str())  ){
            printf("Error: matched file does not contain positive ints");
            exit(0);
        }
        yx.push_back(atoi(split_line[0].c_str())-1);
        xy.push_back(atoi(split_line[1].c_str())-1);
        x2y.push_back({yx[i_tmp],xy[i_tmp]});
        i_tmp++;
    }

    if(i_tmp != num_x_vert){
        printf("Error, the number of matched lines in the input file differs from the "
                "number of observed lines within the wavenumber and intensity thresholds."
                " Matches contained in the file %s should correspond to the observed lines"
                " within the thresholds defined by 'obsrange' and 'obsIthresh'",matching_file_name.c_str());
        exit(0);
    }

    bool swapped;
    for (int i = 0; i < num_x_vert-1; i++){
        swapped = false;
        for (int j = 0; j < num_x_vert-i-1; j++) {
            if (yx[j] > yx[j+1]) {
                swap(&yx[j],&yx[j+1]);
                swap(&xy[j],&xy[j+1]);
                swap2d(&x2y[j],&x2y[j+1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
     }

//    // Here we fill in xy and yx with the missing dummy lines
//    i_tmp = 0;
//    while(i_tmp < num_y_vert){
//        if(std::count(xy.begin(),xy.end(),i_tmp) == 0){
//            xy.push_back(i_tmp);
////            yx.insert(yx.begin()+i_tmp,xy.size()-1);
//        }
//        yx[xy[i_tmp]] = i_tmp;
//        x2y[i_tmp] = {i_tmp,xy[i_tmp]};
//        i_tmp++;
//
//    }


}

void LinearAssigProb::printMatching(Input *pInput, ObsLinelist *Obs, CalcLinelist *Calc){

    for (int i = 0; i < num_x_vert; i++){
        cout << setw(5) << i+1 << "   " << setw(5) << xy[i]+1 << "    "
             << setw(12) << fixed << setprecision(6) << x_vert[i][0] << "    "  << setw(12) << scientific << setprecision(8) << x_vert[i][1] << "   "
             << setw(12) << fixed << setprecision(6) << y_vert[xy[i]][0] << "    "  << setw(12) << scientific << setprecision(8) << y_vert[xy[i]][1];
        if(pInput->GetPrintMatchInfo()=="none"){
            cout << endl;
        }else if(pInput->GetPrintMatchInfo()=="obs"){
            cout << "   |  Obs line:   " << trim((Obs->spec_lines)[x_vert_idex[i]]) << endl;
        }else if(pInput->GetPrintMatchInfo()=="calc"){
            cout << "   |  Calc line:   " << trim((Calc->spec_lines)[y_vert_idex[xy[i]]]) << endl;
        }else if(pInput->GetPrintMatchInfo()=="all"){
            cout << "   |  Obs line:   " << trim((Obs->spec_lines)[x_vert_idex[i]])
                 << "   |  Calc line:   " << trim((Calc->spec_lines)[y_vert_idex[xy[i]]]) << endl;
        }
    }
    printf("\n\n");

}
