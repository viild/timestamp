#include "timestamp.hh"

const std::string Timestamp::SeparatorToChar() const
{
    switch (this->options.date_separator) {
        case Timestamp::DateSeparator::DASH:
            return "-";
        case Timestamp::DateSeparator::SLASH:
            return "/";
        case Timestamp::DateSeparator::BACKSLASH:
            return "\\";
        case Timestamp::DateSeparator::DOT:
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

const tm Timestamp::GetTm() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);

    switch (this->options.time_type) {
        case Timestamp::TimeType::LOCAL:
            return *localtime(&tt);
        case Timestamp::TimeType::GMT:
            return *gmtime(&tt);
        default:
            throw std::invalid_argument( "Invalid time type in GetTm" );
    }
}

const std::string Timestamp::PutYear(const int year, int length) const
{
    if (length == 2)
        return Format(length, year % 100);
    else
        return Format(length, year);
}

const std::string Timestamp::PutDay(const int day) const
{
    return Format(2, day);
}

const std::string Timestamp::PutMonth(const int month) const
{
    return Format(2, month);
}

const std::string Timestamp::PutHour(const int hours) const
{
    return Format(2, hours);
}

const std::string Timestamp::PutMinutes(const int minutes) const
{
    return Format(2, minutes);
}

const std::string Timestamp::PutSeconds(const int seconds) const
{
    return Format(2, seconds);
}

const std::string Timestamp::PutWeek(tm & TM) const
{
    std::pair<int, int> week_year = GetYearAndWeek(TM);
    if (week_year.second != (GetTm().tm_year + 1900))
        return std::string(Format(2, week_year.first) + "/" + Format(4, week_year.second));
    else
        return Format(2, week_year.first);
}

const std::string Timestamp::PutMilliseconds() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();
    typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24> >::type> days;

    days d = std::chrono::duration_cast<days>(tp);
    tp -= d;
    std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(tp);
    tp -= h;
    std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(tp);
    tp -= m;
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(tp);
    tp -= s;
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp);

    return Format(3, ms.count());
}

const std::string Timestamp::PutMonthAsText(const int month) const
{
    static const std::string months_in_text_short[12] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sept",
        "Oct",
        "Nov",
        "Dec"
    };

    static const std::string months_in_text_full[12] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    switch (this->options.month_as_text_type) {
        case Timestamp::MonthAsTextType::FULL:
            return months_in_text_full[month-1];
        case Timestamp::MonthAsTextType::SHORT:
            return months_in_text_short[month-1];
        default:
            throw std::invalid_argument( "Invalid month as text type" );
    }
}

const std::string Timestamp::PutWeekDay(const int week_day) const
{
    static const std::string week_days_full[7] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    static const std::string week_days_short[7] = {
        "Sun",
        "Mon",
        "Tues",
        "Wed",
        "Thurs",
        "Fri",
        "Sat"
    };

    switch (this->options.day_as_text_type) {
        case Timestamp::DayAsTextType::FULL:
            return week_days_full[week_day];
        case Timestamp::DayAsTextType::SHORT:
            return week_days_short[week_day];
        default:
            throw std::invalid_argument( "Invalid day as text type" );
    }
}

const std::string Timestamp::PutOffset(tm & TM, bool separate) const
{
    const int offset = TM.tm_gmtoff;
    std::stringstream string_stream;

    int offset_hours = abs(offset / 3600);
    int offset_mins = (abs(offset) - offset_hours * 3600) / 60;

    string_stream << ((offset < 0) ? "-" : "+")
                  << Format(2, offset_hours)
                  << (separate ? ":" : "")
                  << Format(2, offset_mins);

    return string_stream.str();
}

const std::string Timestamp::PutTimezone(tm & TM, const Timestamp::TimezoneType_t timezone_type) const
{
    switch (timezone_type) {
        case Timestamp::TimezoneType::SHORT:
            return TM.tm_zone;
        case Timestamp::TimezoneType::GMT_OFFSET:
            return ("GMT" + PutOffset(TM, true));
        case Timestamp::TimezoneType::OFFSET:
            return PutOffset(TM, false);
        default:
            throw std::invalid_argument( "Invalid timezone type" );
    }
}

/* Source: https://cplusplus.com/forum/general/220155/ */
const bool Timestamp::IsLeepYear(const int year) const
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0 && year % 400 != 0)
            return false;
        else
            return true;
    }
    return false;
}

/* Source: https://cplusplus.com/forum/general/220155/ */
const std::pair<int, int> Timestamp::GetYearAndWeek(tm & TM) const
{
   int year = TM.tm_year + 1900;
   int day = TM.tm_yday;

   int Monday = day - ( TM.tm_wday + 6 ) % 7;                          // Monday this week: may be negative down to 1-6 = -5;
   int MondayYear = 1 + ( Monday + 6 ) % 7;                            // First Monday of the year
   int Monday01 = ( MondayYear > 4 ) ? MondayYear - 7 : MondayYear;    // Monday of week 1: should lie between -2 and 4 inclusive
   int week = 1 + ( Monday - Monday01 ) / 7;                                 // Nominal week ... but see below

   // In ISO-8601 there is no week 0 ... it will be week 52 or 53 of the previous year
   if ( week == 0 )
   {
      year--;
      week = 52;
      if (MondayYear == 3 || MondayYear == 4 || (IsLeepYear(year) && MondayYear == 2 )) week = 53;
   }

   // Similar issues at the end of the calendar year
   if (week == 53)
   {
      int daysInYear = IsLeepYear(year) ? 366 : 365;
      if (daysInYear - Monday < 3)
      {
         year++;
         week = 1;
      }
   }

   return std::make_pair(week, year);
}