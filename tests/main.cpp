#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>

#include "time_test.hh"
#include "date_test.hh"
#include "raw_test.hh"
#include "timestamp_test.hh"

int countSuccessfull(std::string file, int res)
{
    static int result = 0;
    std::ofstream log_file;
    log_file.open("all_unit_tests.log", std::ios::app);
    log_file << "\t" << std::left << std::setw(70) << file << std::setw(30) << ((!res) ? "PASSED" : "FAILED") << std::endl;
    log_file.close();
    std::cout << "\t" << std::left << std::setw(70) << file << std::setw(30) << ((!res) ? "\033[32mPASSED\033[0m" : "\033[31mFAILED\033[0m") << std::endl;
    if (!res)
        result++;
    return result;
}

int verdict(int passed, int kUnitTestNum)
{
    if (passed < kUnitTestNum) {
        std::cout << "\033[31m[FAIL]\033[0m    "
                  << "Some unit tests were failed. The logs are stored in " << "path" << std::endl;
        return 1;
    }
    else {
        std::cout << "\033[32m[SUCCESS]\033[0m "
                  << "All unit tests have been successfully passed!!!" << std::endl;
        return 0;
    }
}

void printRunnig(std::string file)
{
    std::ofstream log_file;
    log_file.open("all_unit_tests.log", std::ios::app);
    log_file << std::endl;
    log_file << "Running " << file << std::endl;
    log_file.close();
}

int main()
{
    int kUnitTestNum = 4;
    int passed = 0;

    remove("all_unit_tests.log");

    TimeUt time_test;
    DateUt date_test;
    RawUt raw_test;
    TimestampUt timestamp_test;
    std::cout << "Running " << kUnitTestNum << " unit test(s): " << std::endl;

    printRunnig(time_test.returnFileName());
    passed = countSuccessfull(time_test.returnFileName(), time_test.run());
    printRunnig(date_test.returnFileName());
    passed = countSuccessfull(date_test.returnFileName(), date_test.run());
    printRunnig(raw_test.returnFileName());
    passed = countSuccessfull(raw_test.returnFileName(), raw_test.run());
    printRunnig(timestamp_test.returnFileName());
    passed = countSuccessfull(timestamp_test.returnFileName(), timestamp_test.run());

    std::cout << std::endl;

    return verdict(passed, kUnitTestNum);
}
