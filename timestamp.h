#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <string>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdarg>

class Timestamp {
public:
    enum timestamp_format {
        DMY_WITH_MSEC = 0,
        DMY_WITHOUT_MSEC = 1,
        MDY_WITH_MSEC = 2,
        MDY_WITHOUT_MSEC = 3,
        YMD_WITH_MSEC = 4,
        YMD_WITHOUT_MSEC = 5,
        TIME_ONLY_WTIH_MSEC = 6,
        TIME_ONLY_WTIHOUT_MSEC = 7,
        DMY_DATE_ONLY = 8,
        MDY_DATE_ONLY = 9,
        YMD_DATE_ONLY = 10,
        RAW_STAMP = 11
    };
    enum date_style {
        SLASHES = 0,
        DASHES = 1,
        DOTS = 2
    };
    enum time_style {
        WITH_OFFSET_12_H = 0,
        WITH_OFFSET_24_H = 1,
        WITHOUT_OFFSET_12_H = 2,
        WITHOUT_OFFSET_24_H = 3
    };
    Timestamp();
    Timestamp(Timestamp::timestamp_format);
    Timestamp(Timestamp::timestamp_format, Timestamp::date_style);
    Timestamp(Timestamp::timestamp_format, Timestamp::time_style);
    Timestamp(Timestamp::timestamp_format, Timestamp::date_style, Timestamp::time_style);
    std::string get();
private:
    enum timestamp_format ts_format;
    enum date_style d_style;
    enum time_style t_style;
    bool use_24_hour_format;
    bool use_offset;
    std::string pattern;
    void buildPattern();
    std::string buildTimestamp(const char * fmt, ...);
    std::string convertTime(int hour);
};



#endif /* TIMESTAMP_H_ */
