#ifndef TS_TIMESTAMP_H_
#define TS_TIMESTAMP_H_

#include <memory>
#include "ts_time.h"
#include "ts_date.h"
#include "ts_raw.h"

class Timestamp {
public:
    enum class TimestampFormat {
        DMY, MDY, YMD, DMY_DATE_ONLY, MDY_DATE_ONLY, YMD_DATE_ONLY, TIME_ONLY, RAW
    };
    Timestamp(const TimestampFormat & _timestamp_format);
    Timestamp(const TimestampFormat & _timestamp_format,
              const timestamp::Date::DateSeparator & _date_separator);
    Timestamp(const TimestampFormat & _timestamp_format,
              const timestamp::Time::TimeFormat & _time_format);
    Timestamp(const TimestampFormat & _timestamp_format,
              const timestamp::Time::TimeFormat & _time_format, const bool & offset, const bool & msec);
    Timestamp(const TimestampFormat & _timestamp_format,
              const timestamp::Date::DateSeparator & _date_separator,
              const timestamp::Time::TimeFormat & _time_format);
    Timestamp(const TimestampFormat & _timestamp_format,
              const timestamp::Date::DateSeparator & _date_separator,
              const timestamp::Time::TimeFormat & _time_format, const bool & offset, const bool & msec);
    Timestamp(const Timestamp & timestamp);
    Timestamp & operator=(const Timestamp & timestamp);
    const std::string Get() const;
private:
    typedef struct ObjectData {
        TimestampFormat timestamp_format;
        timestamp::Date::DateSeparator date_separator;
        timestamp::Time::TimeFormat time_format;
        bool offset;
        bool msec;
    } ObjectData_t;
    TimestampFormat timestamp_format;
    std::unique_ptr<timestamp::Time> time_obj;
    std::unique_ptr<timestamp::Date> date_obj;
    std::unique_ptr<timestamp::Raw> raw_obj;
    const std::pair<int, std::string> BuildTimestamp(ObjectData_t data);
};

#endif /* TS_TIMESTAMP_H_ */
