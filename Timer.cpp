/*
 * Timer.cpp
 *
 *  Created on: 28 Apr 2020
 *      Author: Phillip
 */

#include "Timer.h"
#include <iostream>

using namespace std::chrono;
using namespace std;

void Timer::StartTimer(string timer_type){

    if(time_data[timer_type].started)
        printf("Attempted to start timer %s but it has already been started!\n",timer_type.c_str());

    initializeTimer(timer_type);

    time_data[timer_type].started = true;

    time_data[timer_type].start = chrono::steady_clock::now();

}


void Timer::EndTimer(string timer_type){

    if(!time_data[timer_type].started){

        printf("Timer %s has not been started!",time_data[timer_type].type.c_str());

    }else if(time_data[timer_type].finished){

        printf("Timer %s has already finished!",time_data[timer_type].type.c_str());

    }else{

        time_data[timer_type].finished = true;

        time_data[timer_type].end = chrono::steady_clock::now();

        time_data[timer_type].exec_time_in_ms = time_data[timer_type].end - time_data[timer_type].start;

    }

}


void Timer::printTimerData(string timer_type){

    if(!time_data[timer_type].started){

        printf("Timer %s has not been started!",time_data[timer_type].type.c_str());

    }else if(!time_data[timer_type].finished){

        printf("Timer %s has not finished!",time_data[timer_type].type.c_str());

    }else{

        printf("Time taken to %s was %6.3f seconds\n",time_data[timer_type].type.c_str(),
                (time_data[timer_type].exec_time_in_ms.count()/1000.0));

    }

    (this->*resetTimer)(timer_type);

}


void Timer::initializeTimer(std::string timer_type){

    time_data[timer_type].type = timer_type;
    time_data[timer_type].started = false;
    time_data[timer_type].finished = false;

}

