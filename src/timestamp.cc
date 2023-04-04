#include "timestamp.hh"
#include <iostream>

Timestamp::TimestampOptions & Timestamp::TimestampOptions::operator=(const Timestamp::TimestampOptions & timestamp_options)
{
    timestamp_format = timestamp_options.timestamp_format;
    date_separator = timestamp_options.date_separator;
    time_format = timestamp_options.time_format;
    time_type = timestamp_options.time_type;
    time_date_appearance = timestamp_options.time_date_appearance;
    month_as_text_type = timestamp_options.month_as_text_type;
    day_as_text_type = timestamp_options.day_as_text_type;
    show_utc_offset = timestamp_options.show_utc_offset;
    show_seconds = timestamp_options.show_seconds;
    show_milliseconds = timestamp_options.show_milliseconds;
    pattern = timestamp_options.pattern;
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
    tm TM = GetTm();

    switch (this->options.timestamp_format) {
        case TimestampFormat::DAY_MONTH_YEAR:
        case TimestampFormat::MONTH_DAY_YEAR:
        case TimestampFormat::YEAR_MONTH_DAY:
            switch (this->options.time_date_appearance) {
                case TimeDateAppearance::ALL:
                    result << GetDate(TM) << " " << GetTime(TM);
                    return result.str();
                case TimeDateAppearance::DATE_ONLY:
                    return GetDate(TM);
                case TimeDateAppearance::TIME_ONLY:
                    return GetTime(TM);
                default:
                    throw std::invalid_argument( "Invalid time and date appearance" );
            }
            break;
        case TimestampFormat::RAW:
            return GetRaw();
        case TimestampFormat::CUSTOM:
            return ParsePattern(TM);
        default:
            throw std::invalid_argument( "Invalid date format" );
    }
}

const std::string Timestamp::GetTime(tm & TM) const
{
    std::stringstream string_stream;
    int hours = TM.tm_hour;
    int mins = TM.tm_min;
    int secs = TM.tm_sec;

    std::pair<int, std::string> time_period = GetPeriod(hours);

    if (this->options.time_format == TimeFormat::TIME_12_H)
        hours = time_period.first;

    string_stream << PutHour(hours) << ":" << PutMinutes(mins);

    if (this->options.show_seconds)
        string_stream << ":" << PutSeconds(secs);

    if (this->options.show_milliseconds)
        string_stream << "." << PutMilliseconds();

    if (this->options.time_format == TimeFormat::TIME_12_H) {
        string_stream << " " << time_period.second;
    }

    if (this->options.show_utc_offset)
        string_stream << " UTC " << PutOffset(TM, false);

    return string_stream.str();    
}

const std::string Timestamp::GetDate(tm & TM) const
{
    int day = TM.tm_mday;
    int month = TM.tm_mon + 1;
    int year = TM.tm_year + 1900;

    std::stringstream string_stream;
    std::string order[3];

     switch (this->options.timestamp_format) {
        case TimestampFormat::DAY_MONTH_YEAR: {
            order[0] = PutDay(day);
            order[1] = (this->options.month_as_text_type != MonthAsTextType::NONE ? PutMonthAsText(month) : PutMonth(month));
            order[2] = PutYear(year, 4);
            break;
        }
        case TimestampFormat::MONTH_DAY_YEAR: {
            order[0] = (this->options.month_as_text_type != MonthAsTextType::NONE ? PutMonthAsText(month) : PutMonth(month));
            order[1] = PutDay(day);
            order[2] = PutYear(year, 4);
            break;
        }
       case TimestampFormat::YEAR_MONTH_DAY: {
            order[0] = PutYear(year, 4);
            order[1] = (this->options.month_as_text_type != MonthAsTextType::NONE ? PutMonthAsText(month) : PutMonth(month));
            order[2] = PutDay(day);
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

const std::string Timestamp::ParsePattern(tm & TM) const
{
    const int length = this->options.pattern.length();
    std::stringstream string_stream;

    const int year = TM.tm_year + 1900;
    const int month = TM.tm_mon + 1;
    const int day = TM.tm_mday;
    const int week_day = TM.tm_wday;
    const int year_day = TM.tm_yday + 1;
    const int mins = TM.tm_min;
    const int seconds = TM.tm_sec;
    int hours = TM.tm_hour;

    std::pair<int, std::string> time_period = GetPeriod(hours);

    if (this->options.time_format == TimeFormat::TIME_12_H)
        hours = time_period.first;

    for (int i = 0; i < length; i++) {
        switch (this->options.pattern[i]) {
            case 'y':
                if (i + 3 < length && this->options.pattern[i+1] == 'y' && this->options.pattern[i+2] == 'y'
                            && this->options.pattern[i+3] == 'y') {
                    string_stream << PutYear(year, 4);
                    i+=3;
                    continue;
                } else if (i + 1 < length && this->options.pattern[i+1] == 'y') {
                    string_stream << PutYear(year, 2);
                    i++;
                    continue;
                } else {
                    continue;
                }
            case 'd':
                if (i + 1 < length && this->options.pattern[i+1] == 'd') {
                    string_stream << PutDay(day);
                    i++;
                    continue;
                } else {
                    continue;
                }
            case 'M':
                if (i + 1 < length && this->options.pattern[i+1] == 'M') {
                    string_stream << PutMonth(month);
                    i++;
                    continue;
                } else {
                    continue;
                }
            case 'H':
                if (i + 1 < length && this->options.pattern[i+1] == 'H') {
                    string_stream << PutHour(hours);
                    i++;
                    continue;
                } else {
                    continue;
                }
            case 'm':
                if (i + 1 < length && this->options.pattern[i+1] == 'm') {
                    string_stream << PutMinutes(mins);
                    i++;
                    continue;
                } else {
                    continue;
                }
            case 's':
                if (i + 1 < length && this->options.pattern[i+1] == 's') {
                    string_stream << PutSeconds(seconds);
                    i++;
                    continue;
                } else {
                    continue;
                }
            case 'w':
                string_stream << PutWeek(TM);
                continue;
            case 'S':
                if (i + 2 < length && this->options.pattern[i+1] == 'S' && this->options.pattern[i+2] == 'S') {
                    string_stream << PutMilliseconds();
                    i+=2;
                    continue;
                } else {
                    continue;
                }
            case 'D':
                string_stream << std::string(std::to_string(year_day));
                continue;
            case 'E':
                string_stream << PutWeekDay(week_day);
                continue;
            case 'a':
                string_stream << (time_period.second);
                continue;
            case 'z':
                if (i + 1 < length && this->options.pattern[i+1] == 'z') {
                    string_stream << PutTimezone(TM, TimezoneType::SHORT);
                    i++;
                    continue;
                } else {
                    string_stream << PutTimezone(TM, TimezoneType::GMT_OFFSET);
                    continue;
                }
            case 'Z':
                string_stream << PutTimezone(TM, TimezoneType::OFFSET);
                continue;
            default:
                string_stream << this->options.pattern[i];
                continue;
        }
    }

    return string_stream.str();
}