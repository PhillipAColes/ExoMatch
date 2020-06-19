/*
 * Utils.cpp
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */
#include "Utils.h"

// Split string
std::vector<std::string> split(std::string const &input) {
    std::istringstream buf(input);
    std::vector<std::string> ret((std::istream_iterator<std::string>(buf)),
                                 std::istream_iterator<std::string>());
    return ret;
}

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

// Check to see if we have a float or string. Returns TRUE if float or scientific notation
bool isPositiveFloat(const std::string &s){
    std::string::const_iterator it = s.begin();
    bool decimalPoint = false;
    bool sciNotation = false;
    //bool minusSign = false;
    bool sign = false;
    int minSize = 0;
    if(s.size()>0 && (s[0] == '+')){
      it++;
      minSize++;
    }
    while(it != s.end()){
      if(*it == '.'){
        if(!decimalPoint) decimalPoint = true;
        else break;
        if(sciNotation) break;
      }else if(*it == 'e' || *it == 'E'){
        if(!sciNotation) sciNotation = true;
        else break;
      }else if(*it == '-' || *it == '+'){
        if(!sciNotation) break;
       // if(minusSign) break;
       // minusSign = true;
        if(sign) break;
        sign = true;
      }else if(!std::isdigit(*it)){
        break;
      }
      ++it;
    }
    return s.size()>minSize && it == s.end();
}

// Check to see if we have an integer or string. Returns TRUE if integer
bool isPositiveInt(const std::string &s){
    std::string::const_iterator it = s.begin();
    bool decimalPoint = false;
    int minSize = 0;
    if(s.size()>0 && (s[0] == '+')){
      it++;
      minSize++;
    }
    while(it != s.end()){
      if(!std::isdigit(*it)){
        break;
      }
      ++it;
    }
    return s.size()>minSize && it == s.end();
}

// compares string arguments. Returns TRUE if first argument is repeated in list of arguments
bool compStrings(int num,...){
    va_list valist;//declare variable of type va_list
    va_start(valist, num); //initialize valist for num number of arguments
    char *s = va_arg(valist, char*);
    for (int i = 1; i < num; i++){
        char *s1 = va_arg(valist, char*); //get first string to compare to the rest
        if( strcmp(s,s1)==0 ){
            return true;
        }
    }
    va_end(valist); //clean memory reserved for valist
    return false;
}


// return an error
void retError(std::string &s){
    std::cout << "Error: please check input for '" << s << "'" << std::endl;
    exit(0);
}

// return an error
void retLLError(int line_num, std::string file_name){
    printf("Error: invalid input in line number %i of linelist file: %s\n",line_num,file_name.c_str());
    exit(0);
}

// Place first 'nfields' tokens found in string into a vector.
// Input is the string to be split (line), a character separator (separator),
// and the number of tokens to be returned (nfields)
std::vector<std::string> split_sub( std::string line, char separator , int nfields){
    std::vector<std::string> split_line;
    std::string::iterator start = line.begin();
    std::string::iterator end = line.end();
    std::string::iterator next = find(start,end,separator);
    int token_N = 0;
    while(next!=end && token_N < nfields){
        std::string tokn = std::string(start,next);
        start = next + 1;
        next = find(start,end,separator);
        if(tokn == "")continue;
        split_line.push_back(tokn);
        token_N++;
    }
    std::string tokn = std::string(start,next);
    split_line.push_back(tokn);
    return split_line;
}


void printCPPVersion(){
    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";
}

