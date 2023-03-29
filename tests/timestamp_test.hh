#ifndef TIMESTAMP_TEST_H_
#define TIMESTAMP_TEST_H_

#include "unit_test.hh"
#include "timestamp.hh"
#include <list> 

class TimestampUt : public UnitTest {
private:
    const int kMaxDateSets = 256;
    const std::string TYPE = "Timestamp";

    typedef struct property_set {
        Timestamp::TimestampFormat_t timestamp_format;
        Timestamp::DateSeparator_t date_separator;
        Timestamp::TimeFormat_t time_format;
        Timestamp::TimeType_t time_type;
        Timestamp::TimeDateAppearance_t time_date_appearance;
        bool show_utc_offset;
        bool show_seconds;
        bool show_milliseconds;
    } property_set_t;

    std::list<std::pair<Timestamp, std::string>> timestamp_pattern;

    const int kMaxTimestampFormats = 4;
    const int kMaxDateSeparators = 4;
    const int kMaxTimeFormats = 2;
    const int kMaxTimeTypes = 2;
    const int kMaxTimeDateAppearance = 3;

    const bool verifyCompilance(const std::string match, const std::string pattern) const;
    const std::string enumToString(const Timestamp::TimeFormat value) const;
    const std::string enumToString(const Timestamp::DateSeparator value) const;
    const std::string enumToString(const Timestamp::TimestampFormat value) const;
    const std::string enumToString(const Timestamp::TimeType value) const;
    const std::string enumToString(const Timestamp::TimeDateAppearance value) const;
    const std::string BuildPattern(property_set_t properties) const;
    const std::string GetSeparatorAsChar(Timestamp::DateSeparator_t & date_separator) const;
public:
    TimestampUt();
    const int run();
    const std::string returnFileName() const;
};


#endif /* TIMESTAMP_TEST_H_ */