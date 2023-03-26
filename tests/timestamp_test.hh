#ifndef TIMESTAMP_TEST_H_
#define TIMESTAMP_TEST_H_

#include "unit_test.hh"
#include "ts_timestamp.hh"
#include "ts_time.hh"
#include "ts_date.hh"

class TimestampUt : public UnitTest {
private:
    const int kMaxDateSets = 256;
    const std::string TYPE = "Timestamp";
    typedef struct property_set {
        Timestamp::TimestampFormat timestamp_format;
        timestamp::Date::DateSeparator date_separator;
        timestamp::Time::TimeFormat time_format;
        bool show_offset;
        bool show_msec;
    } property_set_t;
public:
    TimestampUt();
    const int run();
    const bool verifyCompilance(const std::string match, const std::string pattern) const;
    const std::string enumToString(const timestamp::Time::TimeFormat value) const;
    const std::string enumToString(const timestamp::Date::DateSeparator value) const;
    const std::string enumToString(const Timestamp::TimestampFormat value) const;
    const int generateKey(property_set_t set) const;
    const std::string returnFileName() const;
};


#endif /* TIMESTAMP_TEST_H_ */