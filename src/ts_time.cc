#include "ts_time.h"

namespace timestamp {

/**
 *  Time - class constructor
 *  @_time_format: time format specifier
 *
 *  This constructor creates an object of the Time class. This also sets variable
 *  time_format by values given by an user. The variables show_offset and show_msec
 *  are set to default value (false).
 */
Time::Time(const TimeFormat & _time_format) :
    time_format(_time_format), show_offset(false), show_msec(false)
{}

/**
 *  Time - class constructor
 *  @_time_format: time format specifier
 *  @offset: defines whether UTC offset is shown or not.
 *  @msec: defines whether milliseconds is shown or not.
 *
 *  This constructor creates an object of the Time class. This also sets variables
 *  time_format, offset and msec by values given by an user.
 */
Time::Time(const TimeFormat & _time_format, const bool & offset, const bool & msec) :
    time_format(_time_format), show_offset(offset), show_msec(msec)
{}

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
    tm utc_tm = *gmtime(&tt);

    int hours = 0, mins = 0;
    if (this->show_offset) {
        hours = utc_tm.tm_hour;
        mins = utc_tm.tm_min;
    } else {
        hours = local_tm.tm_hour;
        mins = local_tm.tm_min;
    }
    int offset = local_tm.tm_gmtoff;
    int secs = local_tm.tm_sec;
    int msec = ms.count();
    char offset_char;
    if (offset < 0)
        offset_char = '-';
    else
        offset_char = '+';

    int offset_hours = abs(offset / 3600);
    int offset_mins = (abs(offset) - offset_hours * 3600) / 60;

    PairIntString time_period = GetPeriod(hours);
    std::stringstream string_stream;

    switch (this->time_format) {
        case Time::TimeFormat::TIME_24_H: {
            string_stream << AuxStamp::Format(2, hours) << ":"
                          << AuxStamp::Format(2, mins) << ":"
                          << AuxStamp::Format(2, secs)
                          << GetMsec(msec)
                          << GetOffset(offset_char, offset_hours, offset_mins);
            return string_stream.str();
        }
        case Time::TimeFormat::TIME_12_H: {
            string_stream << AuxStamp::Format(2, time_period.first) << ":"
                          << AuxStamp::Format(2, mins) << ":"
                          << AuxStamp::Format(2, secs)
                          << GetMsec(msec)
                          << " " << time_period.second
                          << GetOffset(offset_char, offset_hours, offset_mins);
            return string_stream.str();
        }
        default:
            throw std::invalid_argument( "Time format is invalid" );
    }
}


/**
 *  GetOffset - builds string with offset if it is required
 *
 *  @offset_char: minus or plus before the offset to specify if the time is ahead or behind UTC
 *  @offset_hour: actual offset in hours
 *  @offset_mins: actual offset in minutes
 *
 *  When required the method build a string with offset from UTC time in the format
 *  UTC +/-HHMM
 */
const std::string Time::GetOffset(char offset_char, int offset_hours, int offset_mins) const
{
    if (!this->show_offset)
        return "";
    std::stringstream string_stream;
    string_stream << " UTC " << offset_char
                  << AuxStamp::Format(2, offset_hours)
                  << AuxStamp::Format(2, offset_mins);
    return string_stream.str();
}

/**
 *  GetMsec - builds string with milliseconds if it is required
 *
 *  @msec: milliseconds to add to time
 *
 *  When required the method build a string with milliseconds.
 */
const std::string Time::GetMsec(int msec) const
{
    if (!this->show_msec)
        return "";
    std::stringstream string_stream;
    string_stream << "." <<  AuxStamp::Format(3, msec);
    return string_stream.str();
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