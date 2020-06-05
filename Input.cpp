/*
 * Input.cpp
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */
#include "Input.h"
#include "Utils.h"

Input::Input(): obs_range_lw(0.0),
                obs_range_up(50000.0),
				calc_range_lw(0.0),
				calc_range_up(50000.0),
				obs_int_thresh(1.0e-40),
				calc_int_thresh(1.0e-40),
				perform_gscd_tf(false),
				read_matches_tf(false),
				cost_coeff(0.5),
				cd_thresh(0.001),
				intens_ratio(0.7),
				max_iter(4),
				gscd_set_size(3),
				num_quanta(0),
				print_match_info("all")
			    {
};


Input::~Input(){}


void Input::SetInFileName(std::string buf){
    in_file_name = buf;
//    std::cout << "User input file is " << in_file_name << std::endl;
}


// Check to see if user input is valid.
void Input::checkInput(vector<string> vs){
    string param_type = trim(vs[0]);
    if(strcmp(param_type.c_str(),"GSCDs")==0){
        return;
    }
    else if(compStrings(3, param_type.c_str(),"obsrange","calcrange")){
        if(vs.size()<3){retError(param_type);}
        if(!isPositiveFloat(vs[1].c_str()) || !isPositiveFloat(vs[2].c_str())){
            retError(param_type);
        }
    }
    else if(compStrings(5, param_type.c_str(),"obsIthresh","calcIthresh",
                           "costcoeff","Iratio")){
        if(vs.size()<2){retError(param_type);}
        if(!isPositiveFloat(vs[1].c_str())){
            retError(param_type);
        }
    }
    else if(compStrings(4, param_type.c_str(),"obsfile","calcfile","readmatches")){
        if(vs.size()<2){retError(param_type);}
    }
    else if(compStrings(4, param_type.c_str(),"numGSCDs","Nquanta","maxiter")){
        if(vs.size()<2){retError(param_type);}
        if(!isPositiveInt(vs[1].c_str())){
            retError(param_type);
        }
    }
    else if( strcmp(param_type.c_str(),"matchinfo")==0 ){
        if(vs.size()<2){retError(param_type);}
        if(!compStrings(5,vs[1].c_str(),"all","none","calc","obs")){
            retError(param_type);
        }
    }
    else if( strcmp(param_type.c_str(),"CDthresh")==0 ){
        if(vs.size()<2){retError(param_type);}
        if( (strcmp(vs[1].c_str(),"read")!=0) && (!isPositiveFloat(vs[1].c_str())) ){
            retError(param_type);
        }
    }
}


void Input::ReadInput(){


    std::ifstream infile(in_file_name.c_str());

    if(infile.fail()){
        cout << "Error: " << in_file_name << " not found. Stopping." << endl;
	    exit(0);
    }

    string in_file_line;

    while(getline(infile,in_file_line)){

    	in_file_line = trim(in_file_line);

        // Split input line into fields
        vector<string> split_line = split(in_file_line);

        if(split_line.size()==0) continue;

        // Check to see if we have a valid input
        checkInput(split_line);

        // Input parameter type
        string param_type = trim(split_line[0]);

        if(param_type == "obsrange"){
            checkInput(split_line);
            obs_range_lw = atof(split_line[1].c_str());
            obs_range_up = atof(split_line[2].c_str());
            if(obs_range_lw > obs_range_up){
                double temp = obs_range_lw;
                obs_range_up = obs_range_lw;
                obs_range_lw = temp;
            }
        }
        else if(param_type == "calcrange"){
            calc_range_lw = atof(split_line[1].c_str());
            calc_range_up = atof(split_line[2].c_str());
            if(calc_range_lw > calc_range_up){
                double temp = calc_range_lw;
                calc_range_up = calc_range_lw;
                calc_range_lw = temp;
                }
        }
        else if(param_type == "obsIthresh"){
            obs_int_thresh = atof(split_line[1].c_str());
        }
        else if(param_type == "calcIthresh"){
            calc_int_thresh = atof(split_line[1].c_str());
        }
        else if(param_type == "obsfile"){
            obs_ll_file_name = split_line[1].c_str();
        }
        else if(param_type == "calcfile"){
            calc_ll_file_name = split_line[1].c_str();
        }
        else if(param_type == "GSCDs"){
            perform_gscd_tf = true;
        }
        else if(param_type == "costcoeff"){
            cost_coeff = atof(split_line[1].c_str());
        }
        else if(param_type == "CDthresh"){
            cd_thresh = atof(split_line[1].c_str());
        }
        else if(param_type == "Iratio"){
            intens_ratio = atof(split_line[1].c_str());
        }
        else if(param_type == "numGSCDs"){
            gscd_set_size = atof(split_line[1].c_str());
        }
        else if(param_type == "Nquanta"){
            num_quanta = atof(split_line[1].c_str());
        }
        else if(param_type == "maxiter"){
            max_iter = atof(split_line[1].c_str());
        }
        else if(param_type == "readmatches"){
            matches_file_name = split_line[1].c_str();
            read_matches_tf = true;
        }
        else if(param_type == "matchinfo"){
            print_match_info = split_line[1].c_str();
        }
        else{
            cout<<"Unrecognized keyword ---> "<< param_type <<endl;
            exit(0);
        }

    }

    infile.close();

};


void Input::printInput(){

    printf("obsfile:    %s\n",obs_ll_file_name.c_str());
    printf("obsrange:    %9.3f  %9.3f\n",obs_range_lw,obs_range_up);
    printf("obsIthresh:    %9.3e\n",obs_int_thresh);

    printf("calcfile:    %s\n",calc_ll_file_name.c_str());
    printf("calcrange:    %9.3f  %9.3f\n",calc_range_lw,calc_range_up);
    printf("calcIthresh:    %9.3e\n",calc_int_thresh);

    printf("matchinfo:    %s\n",print_match_info.c_str());
    if(read_matches_tf){
        printf("readmatches:    %s\n",matches_file_name.c_str());
    }else{
        printf("costcoeff:    %6.3f\n",cost_coeff);
    }

    if(perform_gscd_tf){
        printf("maxiter:    %i\n",max_iter);
        printf("numGSCDs:    %i\n",gscd_set_size);
        printf("Nquanta:    %i\n",num_quanta);
        if(cd_thresh==0){
            printf("CDthresh:    read\n");
        }else{
            printf("CDthresh:    %8.5f\n",cd_thresh);
        }
        printf("Iratio:    %6.3f\n",intens_ratio);
    }

}

