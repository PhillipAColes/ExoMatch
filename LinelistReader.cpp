/*
 * LinelistReader.cpp
 *
 *  Created on: 9 Apr 2020
 *      Author: Phillip
 */

#include "Utils.h"
#include "Input.h"
#include "LinelistReader.h"
#include "ObsLinelist.h"
using namespace std;


LinelistReader::LinelistReader( string ll_type, string ll_file_name ) : linelist_name(ll_file_name),
                                                                        linelist_type(ll_type),
                                                                        num_lines(0){
    cout << "we've initialized a new class" << endl;

};

LinelistReader::~LinelistReader(){}//destructor

void LinelistReader::readObsLinelist(){

    cout << "now we're inside readLinelist obs function" << endl;

}

bool LinelistReader::OpenFile(std::string filename){
    file_stream.open(filename.c_str());
    cout << "file " << filename << " open" << endl;
    if(file_stream.fail()){
        cout << "Error: " << filename << " not found. Stopping." << endl;
        exit(0);
    }
    return file_stream.is_open();
}

bool LinelistReader::CloseFile(){
    if(file_stream.is_open())
        file_stream.close();
    cout << "file closed" << endl;
    return true;
}

