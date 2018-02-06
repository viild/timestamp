#ifndef TS_DATE_H_
#define TS_DATE_H_

#include <chrono>
#include "ts_stamp.h"

namespace timestamp {

class Date {
public:
    enum class DateSeparator {SLASH, DASH, DOT};
    enum class DateFormat {DMY, MDY, YMD};

    Date(const DateSeparator & _date_separator, const DateFormat & _date_format);
    const std::string Get() const;
private:
    DateSeparator date_separator;
    DateFormat date_format;
};

} // namespace timestamp

#endif /* TS_DATE_H_ */
