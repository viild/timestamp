#ifndef TS_TIME_H_
#define TS_TIME_H_

#include "ts_stamp.h"
#include <cassert>
#include <cstdlib>
#include <chrono>

namespace timestamp {

class Time {
public:
    enum class TimeFormat {TIME_12_H, TIME_24_H};
    Time(const TimeFormat & _time_format);
    Time(const TimeFormat & _time_format, const bool & offset, const bool & msec);
    const std::string Get() const;
private:
    TimeFormat time_format;
    bool show_offset;
    bool show_msec;
    const PairIntString GetPeriod(const int hours) const;
};

} // namespace timestamp


#endif /* TS_TIME_H_ */
