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
    std::stringstream string_stream;

    switch (this->time_format) {
        case timestamp::Time::TimeFormat::TIME_24_H:
            if (show_offset && show_msec) {
                string_stream << timestamp::Stamp::PlaceTwoDigits(hours) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(secs) << "."
                    << timestamp::Stamp::PlaceThreeDigits(msec) << " UTC " << offset_char
                    << timestamp::Stamp::PlaceTwoDigits(offset_hours)
                    << timestamp::Stamp::PlaceTwoDigits(offset_mins);
                return string_stream.str();
            } else if (show_offset && !show_msec) {
                string_stream << timestamp::Stamp::PlaceTwoDigits(hours) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(secs) << " UTC " << offset_char
                              << timestamp::Stamp::PlaceTwoDigits(offset_hours)
                              << timestamp::Stamp::PlaceTwoDigits(offset_mins);
                return string_stream.str();
            } else if (!show_offset && show_msec) {
                string_stream << timestamp::Stamp::PlaceTwoDigits(hours) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(secs) << "."
                    << timestamp::Stamp::PlaceThreeDigits(msec);
                return string_stream.str();
            } else {
                string_stream << timestamp::Stamp::PlaceTwoDigits(hours) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(secs);
                return string_stream.str();
            }
            break;
        case timestamp::Time::TimeFormat::TIME_12_H:
            if (show_offset && show_msec) {
                string_stream << timestamp::Stamp::PlaceTwoDigits(time_period.first) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(secs) << "."
                    << timestamp::Stamp::PlaceThreeDigits(msec) << " " << time_period.second
                    << " UTC " << offset_char << timestamp::Stamp::PlaceTwoDigits(offset_hours)
                    << timestamp::Stamp::PlaceTwoDigits(offset_mins);
                return string_stream.str();
            } else if (show_offset && !show_msec) {
                string_stream << timestamp::Stamp::PlaceTwoDigits(time_period.first) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(secs) << " " << time_period.second
                              << " UTC " << offset_char
                              << timestamp::Stamp::PlaceTwoDigits(offset_hours)
                              << timestamp::Stamp::PlaceTwoDigits(offset_mins);
                return string_stream.str();
            } else if (!show_offset && show_msec) {
                string_stream << timestamp::Stamp::PlaceTwoDigits(time_period.first) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                    << timestamp::Stamp::PlaceTwoDigits(secs) << "."
                    << timestamp::Stamp::PlaceThreeDigits(msec) << " " << time_period.second;
                return string_stream.str();
            } else {
                string_stream << timestamp::Stamp::PlaceTwoDigits(time_period.first) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(mins) << ":"
                              << timestamp::Stamp::PlaceTwoDigits(secs) << " "
                              << time_period.second;
                return string_stream.str();
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