// test.h
#ifndef TEST_H_
#define TEST_H_

#include <cstdio>

constexpr const char * pstr = "pass";
constexpr const char * fstr = "fail";

class test {
    const char * tstr = nullptr;    
    unsigned long int pass_count = 0;
    unsigned long int fail_count = 0;
    bool summary_flag = false;
    test(){}                          // no default constructor
public:
    test( const char * );
    void init ( const char * );
    bool summary ( bool flag ) { return summary_flag = flag; }
    bool summary() { return summary_flag; }
    unsigned long int GetPassCount() const { return pass_count; }
    unsigned long int GetFailCount() const { return fail_count; }
    void FlagTest ( const char * description, const int flag );
    void testHungarian();
    void report() const;
};

#endif /* TEST_H_ */
