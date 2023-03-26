#include "ts_timestamp.hh"

/**
 *  Timestamp - class constructor
 *  @_TimestampFormat: timestamp format specifier
 *
 *  This constructor creates an object of the Timestamp class. This also sets variable
 *  timestamp_format by value given by an user. In brackets, this constructor invokes method
 *  BuildTimestamp which builds timestamp pattern based on the "data" values. The exception is
 *  thrown if an error occurred.
 */
Timestamp::Timestamp(const TimestampFormat & _TimestampFormat) :
    timestamp_format(_TimestampFormat)
{
    ObjectData_t data { _TimestampFormat, timestamp::Date::DateSeparator::SLASH,
                        timestamp::Time::TimeFormat::TIME_24_H, false, false };
    std::pair<int, std::string> rv;
    rv = BuildTimestamp(data);
    if (rv.first)
        throw rv.first;
}

/**
 *  Timestamp - class constructor
 *  @_TimestampFormat: timestamp format specifier
 *  @_date_separator: date separator specifier
 *
 *  This constructor creates an object of the Timestamp class. This also sets variable
 *  timestamp_format by value given by an user. In brackets, this constructor invokes method
 *  BuildTimestamp which builds timestamp pattern based on the "data" values. The exception is
 *  thrown if an error occurred.
 */
Timestamp::Timestamp(const TimestampFormat & _TimestampFormat,
                     const timestamp::Date::DateSeparator & _date_separator) :
    timestamp_format(_TimestampFormat)
{
    ObjectData_t data { _TimestampFormat, _date_separator, timestamp::Time::TimeFormat::TIME_24_H,
                        false, false };
    std::pair<int, std::string> rv;
    rv = BuildTimestamp(data);
    if (rv.first)
        throw rv.first;
}

/**
 *  Timestamp - class constructor
 *  @_TimestampFormat: timestamp format specifier
 *  @_time_format: time format specifier
 *
 *  This constructor creates an object of the Timestamp class. This also sets variable
 *  timestamp_format by value given by an user. In brackets, this constructor invokes method
 *  BuildTimestamp which builds timestamp pattern based on the "data" values. The exception is
 *  thrown if an error occurred.
 */
Timestamp::Timestamp(const TimestampFormat & _TimestampFormat,
                     const timestamp::Time::TimeFormat & _time_format) :
    timestamp_format(_TimestampFormat)
{
    ObjectData_t data { _TimestampFormat, timestamp::Date::DateSeparator::SLASH, _time_format,
                        false, false };
    std::pair<int, std::string> rv;
    rv = BuildTimestamp(data);
    if (rv.first)
        throw rv.first;
}

/**
 *  Timestamp - class constructor
 *  @_TimestampFormat: timestamp format specifier
 *  @_time_format: time format specifier
 *  @offset: defines whether UTC offset is shown or not.
 *  @msec: defines whether milliseconds is shown or not.
 *
 *  This constructor creates an object of the Timestamp class. This also sets variable
 *  timestamp_format by value given by an user. In brackets, this constructor invokes method
 *  BuildTimestamp which builds timestamp pattern based on the "data" values. The exception is
 *  thrown if an error occurred.
 */
Timestamp::Timestamp(const TimestampFormat & _TimestampFormat,
                     const timestamp::Time::TimeFormat & _time_format, const bool & offset,
                     const bool & msec) :
    timestamp_format(_TimestampFormat)
{
    ObjectData_t data { _TimestampFormat, timestamp::Date::DateSeparator::SLASH, _time_format,
                        offset, msec };
    std::pair<int, std::string> rv;
    rv = BuildTimestamp(data);
    if (rv.first)
        throw rv.first;
}

/**
 *  Timestamp - class constructor
 *  @_TimestampFormat: timestamp format specifier
 *  @_date_separator: date separator specifier
 *  @_time_format: time format specifier
 *
 *  This constructor creates an object of the Timestamp class. This also sets variable
 *  timestamp_format by value given by an user. In brackets, this constructor invokes method
 *  BuildTimestamp which builds timestamp pattern based on the "data" values. The exception is
 *  thrown if an error occurred.
 */
Timestamp::Timestamp(const TimestampFormat & _TimestampFormat,
                     const timestamp::Date::DateSeparator & _date_separator,
                     const timestamp::Time::TimeFormat & _time_format) :
    timestamp_format(_TimestampFormat)
{
    ObjectData_t data { _TimestampFormat, _date_separator, _time_format, false, false };
    std::pair<int, std::string> rv;
    rv = BuildTimestamp(data);
    if (rv.first)
        throw rv.first;
}

/**
 *  Timestamp - class constructor
 *  @_TimestampFormat: timestamp format specifier
 *  @_date_separator: date separator specifier
 *  @_time_format: time format specifier
 *  @offset: defines whether UTC offset is shown or not.
 *  @msec: defines whether milliseconds is shown or not.
 *
 *  This constructor creates an object of the Timestamp class. This also sets variable
 *  timestamp_format by value given by an user. In brackets, this constructor invokes method
 *  BuildTimestamp which builds timestamp pattern based on the "data" values. The exception is
 *  thrown if an error occurred.
 */
Timestamp::Timestamp(const TimestampFormat & _TimestampFormat,
                     const timestamp::Date::DateSeparator & _date_separator,
                     const timestamp::Time::TimeFormat & _time_format, const bool & offset,
                     const bool & msec) :
    timestamp_format(_TimestampFormat)
{
    ObjectData_t data { _TimestampFormat, _date_separator, _time_format, offset, msec };
    std::pair<int, std::string> rv;
    rv = BuildTimestamp(data);
    if (rv.first)
        throw rv.first;
}

/**
 *  Timestamp - class constructor
 *  @timestamp: timestamp to copy
 *
 *  This constructor copies values from another timestamp object.
 */
Timestamp::Timestamp(const Timestamp & timestamp) :
    timestamp_format(timestamp.timestamp_format),
    time_obj(new timestamp::Time(*timestamp.time_obj)),
    date_obj(new timestamp::Date(*timestamp.date_obj)),
    raw_obj(new timestamp::Raw(*timestamp.raw_obj))
{}

/**
 *  operator= - assignment operator
 *  @timestamp: timestamp to copy
 *
 *  This method copies values from the provided timestamp object
 *  and returns new one.
 */
Timestamp & Timestamp::operator=(const Timestamp & timestamp)
{
  timestamp_format = timestamp.timestamp_format;
  time_obj = std::unique_ptr <timestamp::Time>(new timestamp::Time(*timestamp.time_obj));
  date_obj = std::unique_ptr <timestamp::Date>(new timestamp::Date(*timestamp.date_obj));
  raw_obj = std::unique_ptr <timestamp::Raw>(new timestamp::Raw(*timestamp.raw_obj));
  return *this;
}

/**
 *  BuildTimestamp - form pattern of the class Timestamp
 *  @data: data to use
 *
 *  This method forms the pattern string based on various variable's values
 *  in data structure.
 */
const std::pair<int, std::string> Timestamp::BuildTimestamp(ObjectData_t data)
{
    switch (data.timestamp_format) {
        case TimestampFormat::DMY:
            date_obj = std::unique_ptr < timestamp::Date >
                (new timestamp::Date(data.date_separator, timestamp::Date::DateFormat::DMY));
            time_obj = std::unique_ptr < timestamp::Time >
                (new timestamp::Time(data.time_format, data.offset, data.msec));
            break;
        case TimestampFormat::MDY:
            date_obj = std::unique_ptr < timestamp::Date >
                (new timestamp::Date(data.date_separator, timestamp::Date::DateFormat::MDY));
            time_obj = std::unique_ptr < timestamp::Time >
                (new timestamp::Time(data.time_format, data.offset, data.msec));
            break;
        case TimestampFormat::YMD:
            date_obj = std::unique_ptr < timestamp::Date >
                (new timestamp::Date(data.date_separator, timestamp::Date::DateFormat::YMD));
            time_obj = std::unique_ptr < timestamp::Time >
                (new timestamp::Time(data.time_format, data.offset, data.msec));
            break;
        case TimestampFormat::DMY_DATE_ONLY:
            date_obj = std::unique_ptr < timestamp::Date >
                (new timestamp::Date(data.date_separator, timestamp::Date::DateFormat::DMY));
            break;
        case TimestampFormat::MDY_DATE_ONLY:
            date_obj = std::unique_ptr < timestamp::Date >
                (new timestamp::Date(data.date_separator, timestamp::Date::DateFormat::MDY));
            break;
        case TimestampFormat::YMD_DATE_ONLY:
            date_obj = std::unique_ptr < timestamp::Date >
                (new timestamp::Date(data.date_separator, timestamp::Date::DateFormat::YMD));
            break;
        case TimestampFormat::TIME_ONLY:
            time_obj = std::unique_ptr < timestamp::Time >
                (new timestamp::Time(data.time_format, data.offset, data.msec));
            break;
        case TimestampFormat::RAW:
            raw_obj = std::unique_ptr < timestamp::Raw > (new timestamp::Raw());
            break;
        default:
            return std::make_pair(1, "Invalid argument timestamp_format");
    }
    return std::make_pair(0, "No error");
}

/**
 *  Get - return timestamp in specific format
 *
 *  This method forms timestamp string based on values obtained by "Get" method of class
 *  Raw/Time/Date.
 */
const std::string Timestamp::Get() const
{
    std::string result;
    switch (this->timestamp_format) {
        case TimestampFormat::DMY:
        case TimestampFormat::MDY:
        case TimestampFormat::YMD:
            result = date_obj->Get();
            result += " ";
            result += time_obj->Get();
            return result;
        case TimestampFormat::DMY_DATE_ONLY:
        case TimestampFormat::MDY_DATE_ONLY:
        case TimestampFormat::YMD_DATE_ONLY:
            return date_obj->Get();
        case TimestampFormat::TIME_ONLY:
            return time_obj->Get();
        case TimestampFormat::RAW:
            return raw_obj->Get();
        default:
            return "";
    }
}
