/*
 * Timer.h
 *
 *  Created on: 28 Apr 2020
 *      Author: Phillip
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <string>
#include <ctime>
#include <map>
#include <chrono>

using namespace std::chrono;
using namespace std;

struct TimeInfo{
    std::string type;
    bool started;
    bool finished;
    time_point<steady_clock> start;
    time_point<steady_clock> end;
    duration <double, milli> exec_time_in_ms;
};


class Timer{
public:
    static Timer & getInstance(){
        static Timer instance;
        return instance;
    }

    void StartTimer(string timer_type);
    void EndTimer(string timer_type);
    void printTimerData(string timer_type);

private:
    Timer(){};
    //~Timer();
    std::map<std::string,TimeInfo> time_data;
    void initializeTimer(string timer_type);
    void (Timer::*resetTimer)(string timer_type) = &initializeTimer;

};



#endif /* TIMER_H_ */
