/*
 * LAP.cpp
 *
 *  Created on: 15 Apr 2020
 *      Author: Phillip
 */

#include "LAP.h"
#include "Utils.h"
#include <math.h>
using namespace std;
#define INF 100000000

LAP::LAP(Input *pInput, ObsLinelist *pObsLinelist, CalcLinelist *pCalcLinelist) : num_x_vert(0),
                                                                                  num_y_vert(0),
                                                                                  N_vert(0),
                                                                                  cost_coeff(pInput->GetCostCoeff()){

    double obs_range_lw = pInput->GetObsRangeLw();
    double obs_range_up = pInput->GetObsRangeUp();
    double calc_range_lw = pInput->GetCalcRangeLw();
    double calc_range_up = pInput->GetCalcRangeUp();
    double obs_int_thresh = pInput->GetObsIntThresh();
    double calc_int_thresh = pInput->GetCalcIntThresh();

    vector<double> obs_wn = pObsLinelist->GetWn();
    vector<double> obs_intens = pObsLinelist->GetIntens();

    vector<double> calc_wn = pCalcLinelist->GetWn();
    vector<double> calc_intens = pCalcLinelist->GetIntens();

    for ( int i = 0 ; i < obs_wn.size() ; i++ ){
        if (obs_wn[i] > obs_range_lw && obs_wn[i] < obs_range_up && obs_intens[i] > obs_int_thresh){
            x_vert.push_back({obs_wn[i],obs_intens[i]});
            x_vert_idex.push_back(i);
            num_x_vert++;
        }
    }

    for ( int j = 0 ; j < calc_wn.size() ; j++ ){
        if (calc_wn[j] > calc_range_lw && calc_wn[j] < calc_range_up && calc_intens[j] > calc_int_thresh){
            y_vert.push_back({calc_wn[j],calc_intens[j]});
            y_vert_idex.push_back(j);
            num_y_vert++;
        }
    }
    cout << "number of experimental lines in matching: " << num_x_vert << endl;
    cout << "number of theoretical lines in matching: " << num_y_vert << endl;

    N_vert = num_y_vert;

};

LAP::~LAP(){}


void LAP::generateCostMatrix(){

    double maxcost = 0;

    cost.resize(num_y_vert,vector<double>(num_y_vert));

    cout << "Coefficient of intensity contribution to cost matrix = " << cost_coeff << '\n' << std::endl;
    cout << "Generating cost matrix" << endl;

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

}


void LAP::Hungarian(){

//    cost.resize(n,vector<double>(n));
//    lx.resize(n);
//    ly.resize(n);

    xy.resize(N_vert);
    yx.resize(N_vert);
    S.resize(N_vert);
    T.resize(N_vert);
    slack.resize(N_vert);
    slackx.resize(N_vert);
    previous.resize(N_vert);

    generateCostMatrix();

    initLabels();

    xy.assign(N_vert,-1);
    yx.assign(N_vert,-1);

    max_match = 0;

    while (max_match<N_vert){
        augment();
    }

    for (int x = 0; x < num_x_vert; x++)
        cout << x <<"  "<< xy[x] << endl;

}

void LAP::initLabels(){

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


void LAP::updateLabels(){

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


void LAP::addToTree(int i_vert, int prev_i_vert){
    S[i_vert] = true; //add x to S
    previous[i_vert] = prev_i_vert; //we need this when augmenting

    for (int j_vert = 0; j_vert < N_vert; j_vert++){                    //update slacks, because we add new vertex to S
        if (lx[i_vert] + ly[j_vert] - cost[i_vert][j_vert] < slack[j_vert]){
            slack[j_vert] = lx[i_vert] + ly[j_vert] - cost[i_vert][j_vert];  //minimum residual lx[x]+ly[y]-cost[x][y] for each y
            slackx[j_vert] = i_vert;                          //and x that minimum belongs to
        }
    }
}


void LAP::augment(){ //main function of the algorithm

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
