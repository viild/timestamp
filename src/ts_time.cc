#include "ts_time.h"

namespace timestamp {

/**
 *  Time - class constructor
 *  @_time_format: time format specifier
 *
 *  This constructor creates an object of the Time class. This also invokes constructor
 *  of the Stamp class and sets variable time_format by values given by an user. The
 *  variables show_offset and show_msec are set to default value (false).
 *  In brackets, it prepares pattern and throws the exception if error occurred.
 */
Time::Time(const TimeFormat & _time_format) :
    Stamp(), time_format(_time_format), show_offset(false), show_msec(false)
{
    PairIntString rv;
    rv = BuildPattern();
    if (rv.first)
        throw rv.first;
}

/**
 *  Time - class constructor
 *  @_time_format: time format specifier
 *  @offset: defines whether UTC offset is shown or not.
 *  @msec: defines whether milliseconds is shown or not.
 *
 *  This constructor creates an object of the Time class. This also invokes constructor
 *  of the Stamp class and sets variables time_format, offset and msec by values given
 *  by an user. In brackets, it prepares pattern and throws the exception if error occurred.
 */
Time::Time(const TimeFormat & _time_format, const bool & offset, const bool & msec) :
    Stamp(), time_format(_time_format), show_offset(offset), show_msec(msec)
{
    PairIntString rv;
    rv = BuildPattern();
    if (rv.first)
        throw rv.first;
}

/**
 *  BuildPattern - form pattern of the class Time
 *
 *  This method forms the pattern string based on user-defined time format
 *  and boolean variables show_offset and show_msec. Once the string is formed,
 *  it is saved in the Stamp class by using "SetPattern" method.
 */
const PairIntString Time::BuildPattern()
{
    std::string local_pattern = "";
    switch (this->time_format) {
        case timestamp::Time::TimeFormat::TIME_24_H:
            if (show_offset && show_msec) {
                local_pattern = "%02d:%02d:%02d.%03d UTC %c%02d%02d";
            } else if (show_offset && !show_msec) {
                local_pattern = "%02d:%02d:%02d UTC %c%02d%02d";
            } else if (!show_offset && show_msec) {
                local_pattern = "%02d:%02d:%02d.%03d";
            } else {
                local_pattern = "%02d:%02d:%02d";
            }
            break;
        case timestamp::Time::TimeFormat::TIME_12_H:
            if (show_offset && show_msec) {
                local_pattern = "%02d:%02d:%02d.%03d %s UTC %c%02d%02d";
            } else if (show_offset && !show_msec) {
                local_pattern = "%02d:%02d:%02d %s UTC %c%02d%02d";
            } else if (!show_offset && show_msec) {
                local_pattern = "%02d:%02d:%02d.%03d %s";
            } else {
                local_pattern = "%02d:%02d:%02d %s";
            }
            break;
        default: local_pattern = "";
    }

    try {
        SetPattern(local_pattern);
    } catch (...) {
        return std::make_pair(1, "Set pattern error");
    }
    return std::make_pair(0, "No error");
}

/**
 *  Get - return time in specific format
 *
 *  This method forms string with current time in format defined by "time_format"
 *  and boolean variables show_offset and show_msec. Once the string is formed,
 *  it is returned.
 */
const std::string Time::Get() const
{
    using namespace std;
    using namespace std::chrono;
    /* Only for milliseconds calculation */
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
    /*--------------------------------------------*/

    time_t tt = system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);

    auto hours = local_tm.tm_hour;
    auto mins = local_tm.tm_min;
    auto secs = local_tm.tm_sec;
    auto msec = ms.count();
    auto offset = local_tm.tm_gmtoff;
    char offset_char;
    if (offset < 0)
        offset_char = '-';
    else
        offset_char = '+';

    int offset_hours = abs(offset / 3600);
    int offset_mins = (abs(offset) - offset_hours * 3600) / 60;

    PairIntString time_period = GetPeriod(hours);

    switch (this->time_format) {
        case timestamp::Time::TimeFormat::TIME_24_H:
            if (show_offset && show_msec) {
                return GetValue(GetPattern().c_str(), hours, mins, secs, msec, offset_char,
                                offset_hours, offset_mins);
            } else if (show_offset && !show_msec) {
                return GetValue(GetPattern().c_str(), hours, mins, secs, offset_char, offset_hours,
                                offset_mins);
            } else if (!show_offset && show_msec) {
                return GetValue(GetPattern().c_str(), hours, mins, secs, msec);
            } else {
                return GetValue(GetPattern().c_str(), hours, mins, secs);
            }
            break;
        case timestamp::Time::TimeFormat::TIME_12_H:
            if (show_offset && show_msec) {
                return GetValue(GetPattern().c_str(), time_period.first, mins, secs, msec,
                                time_period.second.c_str(), offset_char, offset_hours, offset_mins);
            } else if (show_offset && !show_msec) {
                return GetValue(GetPattern().c_str(), time_period.first, mins, secs,
                                time_period.second.c_str(), offset_char, offset_hours, offset_mins);
            } else if (!show_offset && show_msec) {
                return GetValue(GetPattern().c_str(), time_period.first, mins, secs, msec,
                                time_period.second.c_str());
            } else {
                return GetValue(GetPattern().c_str(), time_period.first, mins, secs,
                                time_period.second.c_str());
            }
            break;
        default:
            return "";
    }
    return "";
}

/**
 *  GetPeriod - pair <hour_in_12h_format, period as string>
 *  @hours: hours in 24H format
 *
 *  This method returns pair <hour_in_12h_format, period as string> based on "hours" value.
 *  If the value is invalid, assert will be failed.
 */
const PairIntString Time::GetPeriod(const int hours) const
{
    if (hours == 0) {
        return std::make_pair(12, "AM");
    } else if (hours <= 11) {
        return std::make_pair(hours, "AM");
    } else if (hours == 12) {
        return std::make_pair(12, "PM");
    } else if (hours >= 13 && hours <= 23) {
        return std::make_pair(hours-12, "PM");
    }
    /* Should never happen */
    assert(hours < 0 || hours > 23);
    /* Default return to avoid compilation error */
    return std::make_pair(-1, "Error");
}

} // namespace timestamp