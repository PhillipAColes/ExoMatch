// test.cpp
// A simple unit test class

#include "test.h"
#include "../LinearAssigProb.h"

test::test( const char * tstr ) {
    init(tstr);
}

void test::init( const char * tmp_tstr ) {
    tstr = tmp_tstr;
    pass_count = fail_count = 0;
}

void test::FlagTest ( const char * description, const int flag ) {
    const char * pf = nullptr;
    if (flag) {
        pf = pstr;
        ++pass_count;
    } else {
        pf = fstr;
        ++fail_count;
    }
    if(!summary_flag) printf("%s: %s -> %s\n", tstr, description, pf);
}

void test::report() const {
    printf("%s: pass: %ld, fail: %ld\n", tstr, GetPassCount(), GetFailCount());
    fflush(stdout);
}

void test::testHungarian(){   
    // construct LAP object used for testing
    double cost_coeff = 1.0;
    std::vector<std::vector<double>> x_vert({{2,1},{3,1},{1,1}});
    std::vector<std::vector<double>> y_vert({{1.1,1},{2.1,1},{3.1,1},{100,1}});
    LinearAssigProb LAP_test(x_vert, y_vert, cost_coeff); 
    LAP_test.Hungarian();
    std::vector<std::vector<int>> x2y = LAP_test.GetMatching();   
    std::vector<std::vector<int>> expected_x2y = {{0,1},{1,2},{2,0}};
    FlagTest( "Hungarian" , x2y == expected_x2y );
}
