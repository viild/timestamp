#ifndef TIME_TEST_H_
#define TIME_TEST_H_

#include "unit_test.h"
#include "ts_time.h"

class TimeUt : public UnitTest {
private:
    const int kMaxDateSets = 8;
    const std::string TYPE = "Time";
    typedef struct property_set {
        timestamp::Time::TimeFormat time_format;
        bool offset;
        bool msec;
    } property_set_t;
public:
    TimeUt();
    const int run();
    const bool verifyCompilance(const std::string match, const std::string pattern,
                                property_set_t set) const;
    const std::string enumToString(const timestamp::Time::TimeFormat value) const;
    const int generateKey(property_set_t set) const;
    const std::string returnFileName() const;
};



#endif /* TIME_TEST_H_ */
