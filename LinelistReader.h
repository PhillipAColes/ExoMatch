/*
 * LinelistReader.h
 *
 *  Created on: 9 Apr 2020
 *      Author: Phillip
 */

#ifndef LINELISTREADER_H_
#define LINELISTREADER_H_

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Utils.h"
#include "ObsLinelist.h"
using namespace std;

class LinelistReader{
        ifstream file_stream;
        int      num_lines;
        string   linelist_name;
        string   linelist_type;
        void     checkLinelistInput();

    public:
        LinelistReader(string ll_type, string ll_file_name);//constructor
        ~LinelistReader();//destructor
        void    readObsLinelist();
        bool    OpenFile(string ll_fname);
        bool    CloseFile();

};


#endif /* LINELISTREADER_H_ */
