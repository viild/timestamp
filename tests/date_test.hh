#ifndef DATE_TEST_H_
#define DATE_TEST_H_

#include "unit_test.hh"
#include "ts_date.hh"

class DateUt : public UnitTest {
private:
    const int kMaxDateSets = 12;
    const std::string TYPE = "Date";
    typedef struct property_set {
        timestamp::Date::DateFormat date_format;
        timestamp::Date::DateSeparator date_separator;
    } property_set_t;
public:
    DateUt();
    const int run();
    const bool verifyCompilance(const std::string match, const std::string pattern,
                                property_set_t set) const;
    const std::string enumToString(const timestamp::Date::DateFormat value) const;
    const std::string enumToString(const timestamp::Date::DateSeparator value) const;
    const int generateKey(property_set_t set) const;
    const std::string returnFileName() const;
};


#endif /* DATE_TEST_H_ */