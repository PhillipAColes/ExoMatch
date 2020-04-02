/*
 * Utils.cpp
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */
#include "Utils.h"
#include <iterator>
#include <sstream>
using namespace std;


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

// check to see if we have float or string
bool isPositiveFloat(const std::string &s){
    std::string::const_iterator it = s.begin();
    bool decimalPoint = false;
    int minSize = 0;
    if(s.size()>0 && (s[0] == '+')){
      it++;
      minSize++;
    }
    while(it != s.end()){
      if(*it == '.'){
        if(!decimalPoint) decimalPoint = true;
        else break;
      }else if(!std::isdigit(*it)){
        break;
      }
      ++it;
    }
    return s.size()>minSize && it == s.end();
}

// check to see if we have float or string
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

// return an error
void retError(std::string &s){
    cout << "Error: please check input for '" << s << "'" << endl;
    exit(0);
}

