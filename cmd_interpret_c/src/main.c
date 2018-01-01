#include "minunit.h"
#include "cmdline.h"

void test_setup(void) {
}

void test_teardown(void) {
	/* Nothing */
}

MU_TEST(test_fail) {
	mu_fail("Fail now!");
}

char positiveIntArg[] = "123";
char negativeIntArg[] = "-123";
char hexArg[] = "0xCafeBaB3";

MU_TEST(testParseHex)
{
    int output;
    mu_assert(cmdlineParseHex(hexArg, &output) == noError, "cmdlineParseHex should return noError");
    mu_assert_int_eq(0xCafeBaB3, output);
}

MU_TEST(testParsePositiveInt)
{
    int output;
    mu_assert(cmdlineParseInt(positiveIntArg, &output) == noError, "cmdlineParseInt should return noError");
    mu_assert_int_eq(123, output);
}

MU_TEST(testParseNegativeInt)
{
    int output;
    mu_assert(cmdlineParseInt(negativeIntArg, &output) == noError, "cmdlineParseInt should return noError");
    mu_assert_int_eq(-123, output);
}

MU_TEST_SUITE(test_suite) 
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(testParsePositiveInt);
    MU_RUN_TEST(testParseNegativeInt);
    MU_RUN_TEST(testParseHex);
}

int main(int argc, char *argv[]) 
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
