#include "timestamp.hh"
#include <iostream>

Timestamp::TimestampOptions & Timestamp::TimestampOptions::operator=(const Timestamp::TimestampOptions & timestamp_options)
{
    timestamp_format = timestamp_options.timestamp_format;
    date_separator = timestamp_options.date_separator;
    time_format = timestamp_options.time_format;
    time_type = timestamp_options.time_type;
    time_date_appearance = timestamp_options.time_date_appearance;
    show_utc_offset = timestamp_options.show_utc_offset;
    show_seconds = timestamp_options.show_seconds;
    show_milliseconds = timestamp_options.show_milliseconds;
    return *this;
}

Timestamp::Timestamp(const Timestamp & timestamp) :
    options(timestamp.options)
{}

Timestamp & Timestamp::operator=(const Timestamp & timestamp)
{
    options = timestamp.options;
    return *this;
}

const std::string Timestamp::Get() const
{
    std::stringstream result;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();
    time_t tt = std::chrono::system_clock::to_time_t(now);

    switch (this->options.timestamp_format) {
        case TimestampFormat::DAY_MONTH_YEAR:
        case TimestampFormat::MONTH_DAY_YEAR:
        case TimestampFormat::YEAR_MONTH_DAY:
            switch (this->options.time_date_appearance) {
                case TimeDateAppearance::ALL:
                    result << GetDate(tt) << " " << GetTime(tt, tp);
                    return result.str();
                case TimeDateAppearance::DATE_ONLY:
                    return GetDate(tt);
                case TimeDateAppearance::TIME_ONLY:
                    return GetTime(tt, tp);
                default:
                    throw std::invalid_argument( "Invalid time and date appearance" );
            }
            break;
        case TimestampFormat::RAW:
            return GetRaw();
        default:
            throw std::invalid_argument( "Invalid date format" );
    }
}

const std::string Timestamp::GetTime(time_t & tt, std::chrono::system_clock::duration & tp) const
{
    using namespace std;
    using namespace std::chrono;
    /* Only for milliseconds calculation */
    typedef duration<int, ratio_multiply<hours::period, ratio<24> >::type> days;
    
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

    tm local_gmt_time;
    
    switch (this->options.time_type) {
        case TimeType::LOCAL:
            local_gmt_time = *localtime(&tt);
            break;
        case TimeType::GMT:
            local_gmt_time = *gmtime(&tt);
            break;
        default:
            throw std::invalid_argument( "Invalid time type" );
    }

    int hours = local_gmt_time.tm_hour;
    int mins = local_gmt_time.tm_min;
    int offset = local_gmt_time.tm_gmtoff;
    int secs = local_gmt_time.tm_sec;
    int msec = ms.count();

    char offset_char;
    if (offset < 0)
        offset_char = '-';
    else
        offset_char = '+';

    int offset_hours = abs(offset / 3600);
    int offset_mins = (abs(offset) - offset_hours * 3600) / 60;

    std::pair<int, std::string> time_period = GetPeriod(hours);
    std::stringstream string_stream;

    switch (this->options.time_format) {
        case TimeFormat::TIME_24_H: {
            string_stream << Format(2, hours) << ":"
                          << Format(2, mins);
            break;
        }
        case TimeFormat::TIME_12_H: {
            string_stream << Format(2, time_period.first) << ":"
                          << Format(2, mins);
            break;
        }
        default:
            throw std::invalid_argument( "Time format is invalid" );
    }

    if (this->options.show_seconds)
        string_stream << ":" << Format(2, secs);

    if (this->options.show_milliseconds)
        string_stream << "." << Format(3, msec);

    if (this->options.time_format == TimeFormat::TIME_12_H) {
        string_stream << " " << time_period.second;
    }

    if (this->options.show_utc_offset)
        string_stream << " UTC " << offset_char
                      << Format(2, offset_hours)
                      << Format(2, offset_mins);

    return string_stream.str();    
}

const std::string Timestamp::GetDate(time_t & tt) const
{
    tm local_gmt_date;
    
    switch (this->options.time_type) {
        case TimeType::LOCAL:
            local_gmt_date = *localtime(&tt);
            break;
        case TimeType::GMT:
            local_gmt_date = *gmtime(&tt);
            break;
        default:
            throw std::invalid_argument( "Invalid time type" );
    }

    int day = local_gmt_date.tm_mday;
    int month = local_gmt_date.tm_mon + 1;
    int year = local_gmt_date.tm_year + 1900;

    std::stringstream string_stream;
    std::string order[3];

     switch (this->options.timestamp_format) {
        case TimestampFormat::DAY_MONTH_YEAR: {
            order[0] = Format(2, day);
            order[1] = Format(2, month);
            order[2] = Format(4, year);
            break;
        }
        case TimestampFormat::MONTH_DAY_YEAR: {
            order[0] = Format(2, month);
            order[1] = Format(2, day);
            order[2] = Format(4, year);
            break;
        }
       case TimestampFormat::YEAR_MONTH_DAY: {
            order[0] = Format(4, year);
            order[1] = Format(2, month);
            order[2] = Format(2, day);
            break;
        }
        default:
            throw std::invalid_argument( "Invalid date format" );
    }

    string_stream << order[0] << SeparatorToChar()
                  << order[1] << SeparatorToChar()
                  << order[2];
    return string_stream.str();
}

const std::string Timestamp::GetRaw() const
{
    std::stringstream stamp;
    stamp << time(0);
    return stamp.str();
}

const std::string Timestamp::SeparatorToChar() const
{
    switch (this->options.date_separator) {
        case DateSeparator::DASH:
            return "-";
        case DateSeparator::SLASH:
            return "/";
        case DateSeparator::BACKSLASH:
            return "\\";
        case DateSeparator::DOT:
            return ".";
        default:
            throw std::invalid_argument( "Invalid date separator" );
    }
}

const std::string Timestamp::Format(const int n, const int value) const
{
    std::stringstream string_stream;
    string_stream << std::setw(n) << std::setfill('0') << value;
    return string_stream.str();
}

const std::pair<int, std::string> Timestamp::GetPeriod(const int hours) const
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