#include "timestamp_test.hh"
#include <utility>

#ifdef SEPARATE_TEST_BUILD
int main(int argc, char * argv[])
{
    TimestampUt timestamp_test;
    return timestamp_test.run();
}
#endif

TimestampUt::TimestampUt()
{}

const std::string TimestampUt::returnFileName() const
{
    return __FILE__;
}

/**
 *  verifyCompilance - check that match_string matches "pattern" regex and all values are valid
 *  @match_string: string with a time in any format
 *  @pattern: pattern for regex
 *  @set: set to calculate valid values
 *
 *  This function checks that match_string matches the pattern and all the obtained values
 *  are valid. If they are valid, the function will return true. If one of the conditions
 *  wasn't met, it will return false.
 */
const bool TimestampUt::verifyCompilance(const std::string match_string, const std::string pattern) const
{
    return std::regex_match(match_string, std::regex(pattern));
}

/**
 *  enumToString - returns a time format as string
 *  @value: format to return
 *
 *  This function returns a time format as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string TimestampUt::enumToString(const Timestamp::TimeFormat value) const
{
    switch (value) {
        case Timestamp::TimeFormat::TIME_12_H:
            return "Time in 12H format";
        case Timestamp::TimeFormat::TIME_24_H:
            return "Time in 24H format";
        default:
            return "";
    }
}

/**
 *  enumToString - returns a timestamp format as string
 *  @value: format to return
 *
 *  This function returns a timestamp format as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string TimestampUt::enumToString(const Timestamp::TimestampFormat value) const
{
    switch (value) {
        case Timestamp::TimestampFormat::DAY_MONTH_YEAR:
            return "Format is Day Month Year";
        case Timestamp::TimestampFormat::MONTH_DAY_YEAR:
            return "Format is Month Day Year";
        case Timestamp::TimestampFormat::YEAR_MONTH_DAY:
            return "Format is Year Month Day";
        case Timestamp::TimestampFormat::RAW:
            return "RAW";
        default:
            return "";
    }
}

/**
 *  enumToString - returns a date separator as string
 *  @value: format to return
 *
 *  This function returns a date separator as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string TimestampUt::enumToString(const Timestamp::DateSeparator value) const
{
    switch (value) {
        case Timestamp::DateSeparator::SLASH:
            return "SLASH";
        case Timestamp::DateSeparator::DASH:
            return "DASH";
        case Timestamp::DateSeparator::DOT:
            return "DOT";
        case Timestamp::DateSeparator::BACKSLASH:
            return "BACKSLASH";
        default:
            return "";
    }
}

/**
 *  enumToString - returns a time type as string
 *  @value: format to return
 *
 *  This function returns a time type as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
 const std::string TimestampUt::enumToString(const Timestamp::TimeType value) const
{
    switch (value) {
        case Timestamp::TimeType::LOCAL:
            return "LOCAL";
        case Timestamp::TimeType::GMT:
            return "GMT";
        default:
            return "";
    }
}

/**
 *  enumToString - returns a time date appearance as string
 *  @value: format to return
 *
 *  This function returns a time date appearance as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
 const std::string TimestampUt::enumToString(const Timestamp::TimeDateAppearance value) const
{
    switch (value) {
        case Timestamp::TimeDateAppearance::ALL:
            return "ALL";
        case Timestamp::TimeDateAppearance::TIME_ONLY:
            return "TIME_ONLY";
        case Timestamp::TimeDateAppearance::DATE_ONLY:
            return "DATE_ONLY";
        default:
            return "";
    }
}

/**
 *  run - main function in this test module
 *
 *  This function defines all possible time sets, inserts patterns using unique key,
 *  gets result of "get" method of all the Time objects and check the result's correctness.
 */
const int TimestampUt::run()
{
    bool result = true;
    std::string get_result;

    /* The IDEA is to match built object with regex*/
    Timestamp::TimestampFormat_t timestamp_format_set[kMaxTimestampFormats] = {
        {Timestamp::TimestampFormat::DAY_MONTH_YEAR},
        {Timestamp::TimestampFormat::MONTH_DAY_YEAR},
        {Timestamp::TimestampFormat::YEAR_MONTH_DAY},
        {Timestamp::TimestampFormat::RAW}
    };

    Timestamp::DateSeparator_t date_separator_set[kMaxDateSeparators] = {
        {Timestamp::DateSeparator::SLASH},
        {Timestamp::DateSeparator::BACKSLASH},
        {Timestamp::DateSeparator::DOT},
        {Timestamp::DateSeparator::DASH}
    };

    Timestamp::TimeFormat_t time_format_set[kMaxTimeFormats] = {
        {Timestamp::TimeFormat::TIME_12_H},
        {Timestamp::TimeFormat::TIME_24_H}
    };

    Timestamp::TimeType_t time_type_set[kMaxTimeTypes] = {
        {Timestamp::TimeType::LOCAL},
        {Timestamp::TimeType::GMT}
    };

    Timestamp::TimeDateAppearance_t time_date_appearance_set[kMaxTimeDateAppearance] = {
        {Timestamp::TimeDateAppearance::ALL},
        {Timestamp::TimeDateAppearance::TIME_ONLY},
        {Timestamp::TimeDateAppearance::DATE_ONLY}
    };

    /* Bad nested loops but we ok just to build all combinations */
    for (int i = 0; i < kMaxTimestampFormats; i++) {
        for (int j = 0; j < kMaxDateSeparators; j++) {
            for (int k = 0; k < kMaxTimeFormats; k++) {
                for (int p = 0; p < kMaxTimeTypes; p++) {
                    for (int z = 0; z < kMaxTimeDateAppearance; z++) {
                        property_set_t properties;
                        properties.timestamp_format = timestamp_format_set[i];
                        properties.date_separator = date_separator_set[j];
                        properties.time_format = time_format_set[k];
                        properties.time_type = time_type_set[p];
                        properties.time_date_appearance = time_date_appearance_set[z];
                        properties.show_milliseconds = false;
                        properties.show_utc_offset = false;
                        properties.show_seconds = false;

                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    Build(), BuildPattern(properties)));

                        properties.show_milliseconds = false;
                        properties.show_seconds = false;
                        properties.show_utc_offset = true;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddUtcOffset().Build(), BuildPattern(properties)));

                        properties.show_milliseconds = false;
                        properties.show_seconds = true;
                        properties.show_utc_offset = false;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddSeconds().Build(), BuildPattern(properties)));

                        properties.show_milliseconds = true;
                        properties.show_seconds = false;
                        properties.show_utc_offset = false;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddMilliseconds().Build(), BuildPattern(properties)));

                        properties.show_milliseconds = true;
                        properties.show_seconds = false;
                        properties.show_utc_offset = true;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddUtcOffset().AddMilliseconds().Build(), BuildPattern(properties)));

                        properties.show_milliseconds = true;
                        properties.show_seconds = true;
                        properties.show_utc_offset = false;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddSeconds().AddMilliseconds().Build(), BuildPattern(properties)));

                        properties.show_milliseconds = false;
                        properties.show_seconds = true;
                        properties.show_utc_offset = true;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddUtcOffset().AddSeconds().Build(), BuildPattern(properties)));

                        properties.show_milliseconds = true;
                        properties.show_seconds = true;
                        properties.show_utc_offset = true;
                        timestamp_pattern.push_back(std::make_pair(Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_set[i]).
                                    SetDateSeparator(date_separator_set[j]).SetTimeFormat(time_format_set[k]).
                                    SetTimeType(time_type_set[p]).SetTimeDateAppearance(time_date_appearance_set[z]).
                                    AddUtcOffset().AddSeconds().AddMilliseconds().Build(), BuildPattern(properties)));
                    }
                }
            }
        }
    }

    for (std::list<std::pair<Timestamp, std::string>>::iterator it=timestamp_pattern.begin(); it != timestamp_pattern.end(); ++it) {
        /* Just match regex, matching values is to complex action */
        Timestamp * timestamp = &((*it).first);
        std::string timestamp_regex = (*it).second;
        std::string get_result = timestamp->Get();
        bool local_result = verifyCompilance(get_result, timestamp_regex);
        result = result && local_result;

        std::string set_string = enumToString(timestamp->GetTimestampOptions().GetTimestampFormat());
        set_string.append(", ");
        set_string.append(enumToString(timestamp->GetTimestampOptions().GetDateSeparator()));
        set_string.append(", ");
        set_string.append(enumToString(timestamp->GetTimestampOptions().GetTimeFormat()));
        set_string.append(", ");
        set_string.append(enumToString(timestamp->GetTimestampOptions().GetTimeType()));
        set_string.append(", ");
        set_string.append(enumToString(timestamp->GetTimestampOptions().GetTimeDateAppearance()));
        set_string.append(", ");
        set_string.append((timestamp->GetTimestampOptions().GetUtcOffset() ? "Offset enabled" : "Offset disabled"));
        set_string.append(", ");
        set_string.append((timestamp->GetTimestampOptions().GetMilliseconds() ? "Milliseconds enabled" : "Milliseconds disabled"));
        set_string.append(", ");
        set_string.append((timestamp->GetTimestampOptions().GetSeconds() ? "Seconds enabled" : "Seconds disabled"));

        if (!local_result) {
            unexpectedResult(1, TYPE, set_string, get_result);
        } else {
            expectedResult(1, TYPE, set_string, get_result);
        }
    }

    return !result;
}

const std::string TimestampUt::BuildPattern(property_set_t properties) const
{
    std::stringstream date_stream;
    std::stringstream time_stream;
    std::stringstream string_stream;

    std::string date_separator = GetSeparatorAsChar(properties.date_separator);

    switch (properties.timestamp_format) {
        case Timestamp::TimestampFormat::DAY_MONTH_YEAR:
        case Timestamp::TimestampFormat::MONTH_DAY_YEAR:
            date_stream << "(\\d{2})" << date_separator << "(\\d{2})" << date_separator << "(\\d{4})";
            break;
        case Timestamp::TimestampFormat::YEAR_MONTH_DAY:
            date_stream << "(\\d{4})" << date_separator << "(\\d{2})" << date_separator << "(\\d{2})";
            break;
        case Timestamp::TimestampFormat::RAW:
            return "(\\d+)";
        default:
            throw std::invalid_argument( "ERROR 1" );
    }

    switch (properties.time_format) {
        case Timestamp::TimeFormat::TIME_12_H:
        case Timestamp::TimeFormat::TIME_24_H:
            time_stream << "(\\d{2}):(\\d{2})";
            break;
        default:
            throw std::invalid_argument( "ERROR 2" );
    }

    if (properties.show_seconds)
        time_stream << ":(\\d{2})";

    if (properties.show_milliseconds)
        time_stream << ".(\\d{3})";

    if (properties.time_format == Timestamp::TimeFormat::TIME_12_H)
        time_stream << " (AM|PM)";

    if (properties.show_utc_offset)
        time_stream << " UTC [+|-](\\d{2})(\\d{2})";

    switch (properties.time_date_appearance) {
        case Timestamp::TimeDateAppearance::ALL:
            string_stream << date_stream.str() << " " << time_stream.str();
            break;
        case Timestamp::TimeDateAppearance::TIME_ONLY:
            string_stream << time_stream.str();
            break;
        case Timestamp::TimeDateAppearance::DATE_ONLY:
            string_stream << date_stream.str();
            break;
        default:
            throw std::invalid_argument( "ERROR 3" );
    }

    return string_stream.str();
}

const std::string TimestampUt::GetSeparatorAsChar(Timestamp::DateSeparator_t & date_separator) const
{
    switch (date_separator) {
        case Timestamp::DateSeparator::SLASH:
            return "/";
        case Timestamp::DateSeparator::BACKSLASH:
            return "\\\\";
        case Timestamp::DateSeparator::DASH:
            return "-";
        case Timestamp::DateSeparator::DOT:
            return ".";
        default:
            throw std::invalid_argument( "Invalid separator as char" );
    }
}
