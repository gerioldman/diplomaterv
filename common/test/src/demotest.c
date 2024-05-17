#include "TestSuites.h"
#include "UnitTestAssert.h"

void demotest(void);

TestSuite testsuite = {
    .name = "demotest",
    .failed = 0,
    .cleanUpAfter_funcPtr = 0,
    .cleanUpBefore_funcPtr = 0,
    .TestCases = {
        TEST_CASE_ENTRY(demotest),
        TEST_CASE_END
    }
};

TestSuite * testSuites[] = {
    &testsuite,
    TEST_SUITE_END
};


void demotest(void){
    ASSERT_UINT8_EQUAL(0,0);
    ASSERT_UINT8_EQUAL(1,0);
}