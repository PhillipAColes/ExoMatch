/*
 * Utils.h
 *
 *  Created on: 2 Apr 2020
 *      Author: Phillip
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cstdio>
#include <stdio.h>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

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

#endif /* UTILS_H_ */
