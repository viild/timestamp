#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <cstring>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <memory>

class Timestamp {
public:

    typedef enum class TimestampFormat {
        DAY_MONTH_YEAR,
        MONTH_DAY_YEAR,
        YEAR_MONTH_DAY,
        RAW
    } TimestampFormat_t;

    typedef enum class DateSeparator {
        SLASH,
        BACKSLASH,
        DOT,
        DASH
    } DateSeparator_t;

    typedef enum class TimeFormat {
        TIME_12_H,
        TIME_24_H
    } TimeFormat_t;

    typedef enum class TimeType {
        LOCAL,
        GMT
    } TimeType_t;

    typedef enum class TimeDateAppearance {
        ALL,
        TIME_ONLY,
        DATE_ONLY
    } TimeDateAppearance_t;

private:
    class TimestampOptions {
        private:
            TimestampOptions() : timestamp_format(TimestampFormat::DAY_MONTH_YEAR),
                                 date_separator(DateSeparator::SLASH),
                                 time_format(TimeFormat::TIME_24_H),
                                 time_type(TimeType::LOCAL),
                                 time_date_appearance(TimeDateAppearance::ALL),
                                 show_utc_offset(false),
                                 show_seconds(false),
                                 show_milliseconds(false) {

            }

            TimestampOptions(const TimestampOptions & timestamp_options) :
                                timestamp_format(timestamp_options.timestamp_format),
                                date_separator(timestamp_options.date_separator),
                                time_format(timestamp_options.time_format),
                                time_type(timestamp_options.time_type),
                                time_date_appearance(timestamp_options.time_date_appearance),
                                show_utc_offset(timestamp_options.show_utc_offset),
                                show_seconds(timestamp_options.show_seconds),
                                show_milliseconds(timestamp_options.show_milliseconds) {

            }

            TimestampOptions & operator=(const TimestampOptions & timestamp_options);

            TimestampFormat_t timestamp_format;
            DateSeparator_t date_separator;
            TimeFormat_t time_format;
            TimeType_t time_type;
            TimeDateAppearance_t time_date_appearance;
            bool show_utc_offset;
            bool show_seconds;
            bool show_milliseconds;

            friend class Timestamp;
            friend class TimestampBuilder;
        public:
            TimestampFormat_t GetTimestampFormat() {
                return timestamp_format;
            }
            DateSeparator_t GetDateSeparator() {
                return date_separator;
            }
            TimeFormat_t GetTimeFormat() {
                return time_format;
            }
            TimeType_t GetTimeType() {
                return time_type;
            }
            TimeDateAppearance_t GetTimeDateAppearance() {
                return time_date_appearance;
            }
            bool GetUtcOffset() {
                return show_utc_offset;
            }
            bool GetSeconds() {
                return show_seconds;
            }
            bool GetMilliseconds() {
                return show_milliseconds;
            }
    };

public:
    class TimestampBuilder {
        public:
            TimestampBuilder() {}
            
            TimestampBuilder& SetTimestampFormat(TimestampFormat _timestamp_format) {
                options.timestamp_format = _timestamp_format;
                return *this;
            }

            TimestampBuilder& SetDateSeparator(DateSeparator _date_separator) {
                options.date_separator = _date_separator;
                return *this;
            }

            TimestampBuilder& SetTimeFormat(TimeFormat _time_format) {
                options.time_format = _time_format;
                return *this;
            }

            TimestampBuilder& SetTimeType(TimeType _time_type) {
                options.time_type = _time_type;
                return *this;
            }

            TimestampBuilder& SetTimeDateAppearance(TimeDateAppearance _time_date_appearance) {
                options.time_date_appearance = _time_date_appearance;
                return *this;
            }

            TimestampBuilder& AddUtcOffset() {
                options.show_utc_offset = true;
                return *this;
            }

            TimestampBuilder& AddSeconds() {
                options.show_seconds = true;
                return *this;
            }

            TimestampBuilder& AddMilliseconds() {
                options.show_milliseconds = true;
                return *this;
            }

            Timestamp Build() {
                return Timestamp(options);
            }

            Timestamp * BuildPointer() {
                return new Timestamp(options);
            }

        private:
            TimestampOptions options;
    };

private:
    TimestampOptions options;

    const std::string GetDate(time_t & tt) const;
    const std::string GetTime(time_t & tt, std::chrono::system_clock::duration & tp) const;
    const std::string Format(const int n, const int value) const;
    const std::string GetRaw() const;
    const std::string SeparatorToChar() const;
    const std::pair<int, std::string> GetPeriod(const int hours) const;

public:
    Timestamp(const TimestampOptions & options) : options(options) {}
    Timestamp(const Timestamp & timestamp);
    Timestamp & operator=(const Timestamp & timestamp);

    const std::string Get() const;
    TimestampOptions GetTimestampOptions() {
        return options;
    }
};

#endif /* TIMESTAMP_H_ */
