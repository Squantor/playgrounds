#include "minunit.h"
#include "cmdline.h"

void test_setup(void) {
}

void test_teardown(void) {
	/* Nothing */
}

char commandHelp[] = "help\n";

MU_TEST(testParseHelpCommand)
{
    mu_assert(cmdlineParse(commandHelp) == noError, "cmdlineParse should return noError");
}

char commandTest[] = "test 0x100 1024\n";

MU_TEST(testParseTestCommand)
{
    mu_assert(cmdlineParse(commandTest) == noError, "cmdlineParse should return noError");
}

char positiveIntArg[] = "123";
char negativeIntArg[] = "-123";
char hexArg[] = "0xC4f3BaB3";

MU_TEST(testParseHex)
{
    int output;
    mu_assert(cmdlineParseHex(hexArg, &output) == noError, "cmdlineParseHex should return noError");
    mu_assert_int_eq(0xC4f3BaB3, output);
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
    MU_RUN_TEST(testParseTestCommand);
    MU_RUN_TEST(testParseHelpCommand);
}

int main(int argc, char *argv[]) 
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
