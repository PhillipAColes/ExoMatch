/*
 * Input.cpp
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */
#include "Input.h"
#include "Utils.h"

//Constructor to initialise data members in class Input
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
				puts("Initialising default values");
};


Input::~Input(){}//destructor


void Input::SetInFileName(std::string buf){
    in_file_name = buf;
    std::cout << "User input file is " << in_file_name << std::endl;
}


void Input::checkInput(vector<string> vs){
    string param_type = trim(vs[0]);
    if( strcmp(param_type.c_str(),"obsrange")==0  ||
        strcmp(param_type.c_str(),"calcrange")==0 ){
        if(vs.size()<3){
            retError(param_type);
        }
        if(!isPositiveFloat(vs[1].c_str()) || !isPositiveFloat(vs[2].c_str())){
            retError(param_type);
        }
    }
    else if( strcmp(param_type.c_str(),"obsIthresh")==0  ||
             strcmp(param_type.c_str(),"calcIthresh")==0 ||
             strcmp(param_type.c_str(),"costcoeff")==0   ||
             strcmp(param_type.c_str(),"CDthresh")==0    ||
             strcmp(param_type.c_str(),"Iratio")==0      ){
        if(vs.size()<2){
            retError(param_type);
        }
        if(!isPositiveFloat(vs[1].c_str())){
            retError(param_type);
        }
    }
    else if( strcmp(param_type.c_str(),"obsfile")==0    ||
            strcmp(param_type.c_str(),"calcfile")==0    ||
            strcmp(param_type.c_str(),"readmatches")==0 ){
        if(vs.size()<2){retError(param_type);}
    }
    else if( strcmp(param_type.c_str(),"numGSCDs")==0  ||
             strcmp(param_type.c_str(),"Nquanta ")==0  ||
             strcmp(param_type.c_str(),"maxiter")==0  ){
        if(vs.size()<2){retError(param_type);}
        if(!isPositiveInt(vs[1].c_str())){
            retError(param_type);
        }
    }
    else if( strcmp(param_type.c_str(),"matchinfo")==0 ){
        if(vs.size()<2){retError(param_type);}
        if( strcmp(vs[1].c_str(),"all")==0   ||
            strcmp(vs[1].c_str(),"none")==0  ||
            strcmp(vs[1].c_str(),"calc")==0  ||
            strcmp(vs[1].c_str(),"obs")==0   ){
        ;}
        else{
            retError(param_type);
        }
    }
}


void Input::ReadInput(){

    cout << "Will now read file " << in_file_name << std::endl;

    std::ifstream infile(in_file_name.c_str());

    if(infile.fail()){
        cout << "Error: " << in_file_name << " not found. Stopping." << endl;
	    return;
    }

    string in_file_line;

    while(getline(infile,in_file_line)){

    	in_file_line = trim(in_file_line);

        // Split input line into fields
        vector<string> split_line = split(in_file_line);

        if(split_line.size()==0) continue;

        // Input parameter name
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

            checkInput(split_line);

            calc_range_lw = atof(split_line[1].c_str());
            calc_range_up = atof(split_line[2].c_str());

            if(calc_range_lw > calc_range_up){
                double temp = calc_range_lw;
                calc_range_up = calc_range_lw;
                calc_range_lw = temp;
                }
        }
        else if(param_type == "obsIthresh"){

            checkInput(split_line);

            obs_int_thresh = atof(split_line[1].c_str());
        }
        else if(param_type == "calcIthresh"){

            checkInput(split_line);

            calc_int_thresh = atof(split_line[1].c_str());
        }
        else if(param_type == "obsfile"){

            checkInput(split_line);

            obs_ll_file_name = split_line[1].c_str();
        }
        else if(param_type == "calcfile"){

            checkInput(split_line);

            calc_ll_file_name = split_line[1].c_str();

        }
        else if(param_type == "GSCDs"){

            perform_gscd_tf = true;

        }
        else if(param_type == "costcoeff"){

            checkInput(split_line);

            cost_coeff = atof(split_line[1].c_str());

        }
        else if(param_type == "CDthresh"){

            checkInput(split_line);

            cd_thresh = atof(split_line[1].c_str());

        }
        else if(param_type == "Iratio"){

            checkInput(split_line);

            intens_ratio = atof(split_line[1].c_str());

        }
        else if(param_type == "numGSCDs"){

            checkInput(split_line);

            gscd_set_size = atof(split_line[1].c_str());

        }
        else if(param_type == "Nquanta"){

            checkInput(split_line);

            num_quanta = atof(split_line[1].c_str());

        }
        else if(param_type == "maxiter"){

            checkInput(split_line);

            max_iter = atof(split_line[1].c_str());

        }
        else if(param_type == "readmatches"){

            checkInput(split_line);

            matches_file_name = split_line[1].c_str();
            read_matches_tf = true;

        }
        else if(param_type == "matchinfo"){

            checkInput(split_line);

            print_match_info = split_line[1].c_str();

        }
        else{

            cout<<"Unrecognized keyword ---> "<< param_type <<endl;

            exit(0);

        }

    }

    infile.close();

};


