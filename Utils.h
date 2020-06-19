/*
 * Utils.h
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cstring>
#include <sstream>
#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

// trim from start
std::string &ltrim(std::string &s);

// trim from end
std::string &rtrim(std::string &s);

// trim from both ends
std::string &trim(std::string &s);

std::vector<std::string> split(std::string const &input);

bool isPositiveFloat(const std::string &s);

bool isPositiveInt(const std::string &s);

bool compStrings(int num,...);

void retError(std::string &s);

void retLLError(int line_num, std::string file_name);

std::vector<std::string> split_sub( std::string line, char separator , int nfields);

template<typename T>
std::vector<T> slice_vec(std::vector<T> &v, int m, int n)
{
    std::vector<T> vec;
    std::copy(v.begin() + m, v.begin() + n + 1, std::back_inserter(vec));
    return vec;
}

template <typename T>
void swap(T *a, T *b){
    T temp = *a; // value pointed to by a (i.e.*a) is assigned to variable temp
    *a = *b; // value pointed to by b (i.e. *b) is assigned to where a points to
    *b = temp; // value 'temp' is copied into where b points to (*b). Here the address of b doesn't change, the value held at that address does
}

void printCPPVersion();

#endif /* UTILS_H_ */
