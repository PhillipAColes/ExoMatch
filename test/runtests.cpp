// runtest.cpp
#include <cstdio>
#include <cstring>
#include <string>
#include "test.h"
#include "../LinearAssigProb.h"

constexpr bool summary_flag = false;//true;
unsigned long int tpass = 0, tfail = 0;

int main()
{ 
    test u("test");
    u.summary(summary_flag);
   
    printf("\nTesting ExoMatch \n\n");
     
    //testing the linear assignment problem 
    u.testHungarian();
    
    tpass += u.GetPassCount();
    tfail += u.GetFailCount();
    u.report();
    
    printf("\nTotals: pass: %ld, fail: %ld\n", tpass, tfail);
    
    return 0;   // Done. Yay!
}
