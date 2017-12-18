/*#include "timestamp.h"
#include <iostream>
#include <iomanip>

void printElement(std::string string, const int& width)
{
    const char separator    = ' ';
    std::cout << std::left << std::setw(width) << std::setfill(separator) << string;
}

bool hasOffset(Timestamp::time_style var)
{
    switch (var) {
        case Timestamp::time_style::WITH_OFFSET_12_H:
        case Timestamp::time_style::WITH_OFFSET_24_H:
            return true;
        default:
            return false;
    }
}

bool is24hour(Timestamp::time_style var)
{
    switch (var) {
        case Timestamp::time_style::WITH_OFFSET_24_H:
        case Timestamp::time_style::WITHOUT_OFFSET_24_H:
            return true;
        default:
            return false;
    }
}

std::string separator(Timestamp::date_style var)
{
    switch (var) {
        case Timestamp::date_style::SLASHES:
            return "slashes";
        case Timestamp::date_style::DASHES:
            return "dashes";
        case Timestamp::date_style::DOTS:
            return "dots";
    }
    return "";
}

std::string type(Timestamp::timestamp_format var)
{
    switch (var) {
        case Timestamp::timestamp_format::DMY_WITH_MSEC:
            return "DMY with msec";
        case Timestamp::timestamp_format::DMY_WITHOUT_MSEC:
            return "DMY without msec";
        case Timestamp::timestamp_format::MDY_WITH_MSEC:
            return "MDY with msec";
        case Timestamp::timestamp_format::MDY_WITHOUT_MSEC:
            return "MDY without msec";
        case Timestamp::timestamp_format::YMD_WITH_MSEC:
            return "YMD with msec";
        case Timestamp::timestamp_format::YMD_WITHOUT_MSEC:
            return "YMD without msec";
        case Timestamp::timestamp_format::TIME_ONLY_WTIH_MSEC:
            return "TIME ONLY with msec";
        case Timestamp::timestamp_format::TIME_ONLY_WTIHOUT_MSEC:
            return "TIME ONLY without msec";
        case Timestamp::timestamp_format::DMY_DATE_ONLY:
            return "DMY DATE ONLY";
        case Timestamp::timestamp_format::MDY_DATE_ONLY:
            return "MDY DATE ONLY";
        case Timestamp::timestamp_format::YMD_DATE_ONLY:
            return "YMD DATE ONLY";
        case Timestamp::timestamp_format::RAW_STAMP:
            return "RAW ONLY";
    }
    return "";
}

int main()
{
    int number = 0;
    for (int ii = Timestamp::timestamp_format::DMY_WITH_MSEC;
        ii <= Timestamp::timestamp_format::RAW_STAMP; ii++) {
        Timestamp::timestamp_format i = static_cast<Timestamp::timestamp_format>(ii);

        for (int jj = Timestamp::date_style::SLASHES;
            jj <= Timestamp::date_style::DOTS; jj++) {
            Timestamp::date_style j = static_cast<Timestamp::date_style>(jj);

            for (int kk = Timestamp::time_style::WITH_OFFSET_12_H;
                kk <= Timestamp::time_style::WITHOUT_OFFSET_24_H; kk++) {
                Timestamp::time_style k = static_cast<Timestamp::time_style>(kk);

                Timestamp stamp(i, j, k);
                std::string string;
                string = type(i);
                string += ", ";
                string += (hasOffset(k) ? "HAS offset, " : "DOESN'T HAVE offset, ");
                string += "TS is";
                string += (is24hour(k) ? " 24 hour, " : "n't 24 hour, ");
                string += "uses '";
                string += separator(j);
                string += "' separator!";

                printElement(string, 100);
                printElement(stamp.get(), 50);
                std::cout << std::endl;
            }
        }
        std::cout << std::endl << std::endl;
    }


    return 0;
}

*/
