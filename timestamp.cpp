#include "timestamp.h"

Timestamp::Timestamp()
{
    this->ts_format = Timestamp::timestamp_format::DMY_WITHOUT_MSEC;
    this->d_style = Timestamp::date_style::DASHES;
    this->t_style = Timestamp::time_style::WITH_OFFSET_24_H;
    buildPattern();
};

Timestamp::Timestamp(Timestamp::timestamp_format _ts_format)
{
    this->ts_format = _ts_format;
    this->d_style = Timestamp::date_style::DASHES;
    this->t_style = Timestamp::time_style::WITH_OFFSET_24_H;
    buildPattern();
};

Timestamp::Timestamp(Timestamp::timestamp_format _ts_format, Timestamp::date_style _d_style)
{
    this->ts_format = _ts_format;
    this->d_style = _d_style;
    this->t_style = Timestamp::time_style::WITH_OFFSET_24_H;
    buildPattern();
};

Timestamp::Timestamp(Timestamp::timestamp_format _ts_format, Timestamp::time_style _t_style)
{
    this->ts_format = _ts_format;
    this->d_style = Timestamp::date_style::DASHES;
    this->t_style = _t_style;
    buildPattern();
};

Timestamp::Timestamp(Timestamp::timestamp_format _ts_format, Timestamp::date_style _d_style,
                     Timestamp::time_style _t_style)
{
    this->ts_format = _ts_format;
    this->d_style = _d_style;
    this->t_style = _t_style;
    buildPattern();
};

void Timestamp::buildPattern()
{
    char date_symbol;

    switch (d_style) {
        case Timestamp::date_style::SLASHES: date_symbol = '/'; break;
        case Timestamp::date_style::DASHES: date_symbol = '-'; break;
        case Timestamp::date_style::DOTS: date_symbol = '.';
    }
    switch (t_style) {
        case Timestamp::time_style::WITH_OFFSET_12_H:
            this->use_24_hour_format = false;
            this->use_offset = true;
            break;
        case Timestamp::time_style::WITH_OFFSET_24_H:
            this->use_24_hour_format = true;
            this->use_offset = true;
            break;
        case Timestamp::time_style::WITHOUT_OFFSET_12_H:
            this->use_24_hour_format = false;
            this->use_offset = false;
            break;
        case Timestamp::time_style::WITHOUT_OFFSET_24_H:
            this->use_24_hour_format = true;
            this->use_offset = false;
            break;
    }

    switch (ts_format) {
        case Timestamp::timestamp_format::DMY_WITH_MSEC:
        case Timestamp::timestamp_format::MDY_WITH_MSEC:
            this->pattern = "%02d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += date_symbol;
            this->pattern += "%04d";
            this->pattern += " %02d:%02d:%02d";
            this->pattern += (this->use_24_hour_format ? "" : " %s");
            this->pattern += (this->use_offset ? " UTC%c%02d%02d" : "");
            this->pattern += " %04d";
            break;
        case Timestamp::timestamp_format::DMY_WITHOUT_MSEC:
        case Timestamp::timestamp_format::MDY_WITHOUT_MSEC:
            this->pattern = "%02d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += date_symbol;
            this->pattern += "%04d";
            this->pattern += " %02d:%02d:%02d";
            this->pattern += (this->use_24_hour_format ? "" : " %s");
            this->pattern += (this->use_offset ? " UTC%c%02d%02d" : "");
            break;
        case Timestamp::timestamp_format::YMD_WITH_MSEC:
            this->pattern = "%04d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += " %02d:%02d:%02d";
            this->pattern += (this->use_24_hour_format ? "" : " %s");
            this->pattern += (this->use_offset ? " UTC%c%02d%02d" : "");
            this->pattern += " %04d";
            break;
        case Timestamp::timestamp_format::YMD_WITHOUT_MSEC:
            this->pattern = "%04d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += " %02d:%02d:%02d";
            this->pattern += (this->use_24_hour_format ? "" : " %s");
            this->pattern += (this->use_offset ? " UTC%c%02d%02d" : "");
            break;
        case Timestamp::timestamp_format::TIME_ONLY_WTIH_MSEC:
            this->pattern = "%02d:%02d:%02d";
            this->pattern += (this->use_24_hour_format ? "" : " %s");
            this->pattern += (this->use_offset ? " UTC%c%02d%02d" : "");
            this->pattern += " %04d";
            break;
        case Timestamp::timestamp_format::TIME_ONLY_WTIHOUT_MSEC:
            this->pattern = "%02d:%02d:%02d";
            this->pattern += (this->use_24_hour_format ? "" : " %s");
            this->pattern += (this->use_offset ? " UTC%c%02d%02d" : "");
            break;
        case Timestamp::timestamp_format::DMY_DATE_ONLY:
        case Timestamp::timestamp_format::MDY_DATE_ONLY:
            this->pattern = "%02d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += date_symbol;
            this->pattern += "%04d";
            break;
        case Timestamp::timestamp_format::YMD_DATE_ONLY:
            this->pattern = "%04d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            this->pattern += date_symbol;
            this->pattern += "%02d";
            break;
        case Timestamp::timestamp_format::RAW_STAMP:
            this->pattern = "%d";
            break;
    }
}

std::string Timestamp::get()
{
    using namespace std;
    using namespace std::chrono;
    typedef duration<int, ratio_multiply<hours::period, ratio<24> >::type> days;
    system_clock::time_point now = system_clock::now();
    system_clock::duration tp = now.time_since_epoch();
    days d = duration_cast<days>(tp);
    tp -= d;
    hours h = duration_cast<hours>(tp);
    tp -= h;
    minutes m = duration_cast<minutes>(tp);
    tp -= m;
    seconds s = duration_cast<seconds>(tp);
    tp -= s;
    milliseconds ms = duration_cast<milliseconds>(tp);

    time_t tt = system_clock::to_time_t(now);
    tm utc_tm = *gmtime(&tt);
    tm local_tm = *localtime(&tt);

    auto year = local_tm.tm_year + 1900;
    auto month = local_tm.tm_mon + 1;
    auto day = local_tm.tm_mday;
    auto hour = 0;
    if (this->use_24_hour_format)
        hour = local_tm.tm_hour;
    else
        hour = local_tm.tm_hour - 12;
    auto mins = local_tm.tm_min;
    auto secs = local_tm.tm_sec;
    auto msec = ms.count();
    auto hoffset = local_tm.tm_hour - utc_tm.tm_hour;
    auto moffset = local_tm.tm_min - utc_tm.tm_min;

    bool negativeOffset = ((hoffset < 0 || moffset < 0) ? true : false);


    /* If we DOES use 24 hour time format and UTC offset */
    if (this->use_24_hour_format && this->use_offset) {
        switch (ts_format) {
            case Timestamp::timestamp_format::DMY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset, msec);
            case Timestamp::timestamp_format::DMY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset);
            case Timestamp::timestamp_format::MDY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset, msec);
            case Timestamp::timestamp_format::MDY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset);
            case Timestamp::timestamp_format::YMD_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset, msec);
            case Timestamp::timestamp_format::YMD_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset);
            case Timestamp::timestamp_format::TIME_ONLY_WTIH_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset, msec);
            case Timestamp::timestamp_format::TIME_ONLY_WTIHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs,
                                      (negativeOffset ? '-' : '+'), hoffset, moffset);
            case Timestamp::timestamp_format::DMY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), day, month, year);
            case Timestamp::timestamp_format::MDY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), month, day, year);
            case Timestamp::timestamp_format::YMD_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), year, month, day);
            case Timestamp::timestamp_format::RAW_STAMP:
                return buildTimestamp(this->pattern.c_str(), time(0));
        }
    /* If we DON'T use 24 hour time format and UTC offset */
    } else if (!this->use_24_hour_format && this->use_offset) {
        switch (ts_format) {
            case Timestamp::timestamp_format::DMY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset, msec);
            case Timestamp::timestamp_format::DMY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset);
            case Timestamp::timestamp_format::MDY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset, msec);
            case Timestamp::timestamp_format::MDY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset);
            case Timestamp::timestamp_format::YMD_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset, msec);
            case Timestamp::timestamp_format::YMD_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset, msec);
            case Timestamp::timestamp_format::TIME_ONLY_WTIH_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset, msec);
            case Timestamp::timestamp_format::TIME_ONLY_WTIHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs,
                                      convertTime(hour+12).c_str(), (negativeOffset ? '-' : '+'),
                                      hoffset, moffset);
            case Timestamp::timestamp_format::DMY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), day, month, year);
            case Timestamp::timestamp_format::MDY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), month, day, year);
            case Timestamp::timestamp_format::YMD_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), year, month, day);
            case Timestamp::timestamp_format::RAW_STAMP:
                return buildTimestamp(this->pattern.c_str(), time(0));
        }
    /* If we DOES use 24 hour time format and DON'T use UTC offset */
    } else if (this->use_24_hour_format && !this->use_offset) {
        switch (ts_format) {
            case Timestamp::timestamp_format::DMY_WITH_MSEC:
                 return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs, msec);
            case Timestamp::timestamp_format::DMY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs);
            case Timestamp::timestamp_format::MDY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs, msec);
            case Timestamp::timestamp_format::MDY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs);
            case Timestamp::timestamp_format::YMD_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs, msec);
            case Timestamp::timestamp_format::YMD_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs);
            case Timestamp::timestamp_format::TIME_ONLY_WTIH_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs, msec);
            case Timestamp::timestamp_format::TIME_ONLY_WTIHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs);
            case Timestamp::timestamp_format::DMY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), day, month, year);
            case Timestamp::timestamp_format::MDY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), month, day, year);
            case Timestamp::timestamp_format::YMD_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), year, month, day);
            case Timestamp::timestamp_format::RAW_STAMP:
                return buildTimestamp(this->pattern.c_str(), time(0));
        }
    /* If we DON'T use 24 hour time format and DON'T use UTC offset */
    } else {
        switch (ts_format) {
            case Timestamp::timestamp_format::DMY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs,
                                      convertTime(hour+12).c_str(), msec);
            case Timestamp::timestamp_format::DMY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), day, month, year, hour, mins, secs,
                                      convertTime(hour+12).c_str());
            case Timestamp::timestamp_format::MDY_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs,
                                      convertTime(hour+12).c_str(), msec);
            case Timestamp::timestamp_format::MDY_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), month, day, year, hour, mins, secs,
                                      convertTime(hour+12).c_str());
            case Timestamp::timestamp_format::YMD_WITH_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs,
                                      convertTime(hour+12).c_str(), msec);
            case Timestamp::timestamp_format::YMD_WITHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), year, month, day, hour, mins, secs,
                                      convertTime(hour+12).c_str());
            case Timestamp::timestamp_format::TIME_ONLY_WTIH_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs,
                                      convertTime(hour+12).c_str(), msec);
            case Timestamp::timestamp_format::TIME_ONLY_WTIHOUT_MSEC:
                return buildTimestamp(this->pattern.c_str(), hour, mins, secs,
                                      convertTime(hour+12).c_str());
            case Timestamp::timestamp_format::DMY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), day, month, year);
            case Timestamp::timestamp_format::MDY_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), month, day, year);
            case Timestamp::timestamp_format::YMD_DATE_ONLY:
                return buildTimestamp(this->pattern.c_str(), year, month, day);
            case Timestamp::timestamp_format::RAW_STAMP:
                return buildTimestamp(this->pattern.c_str(), time(0));
        }
    }
}

std::string Timestamp::buildTimestamp(const char * fmt, ...)
{
    char string[300];
    va_list args;
    va_start(args, fmt);
    vsprintf(string, fmt, args);
    va_end(args);
    return string;
}

std::string Timestamp::convertTime(int hour)
{
    if (hour >= 12)
        return "P.M.";
    return "A.M.";
}