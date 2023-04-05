#include <iostream>
#include <wlc/timestamp/timestamp.hh>

int main()
{
        /* Custom TimeStamp in 12H time format and show full day of the week */
        Timestamp timestamp = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::CUSTOM).
                                                            SetPattern("E dd-MM-yyyy HH:mm a").
                                                            SetTimeFormat(Timestamp::TimeFormat::TIME_12_H).
                                                            SetDayAsTextType(Timestamp::DayAsTextType::FULL).
                                                            Build();
        std::cout << "Custom TimeStamp in 12H time format and day of the week = " << timestamp.Get().c_str() << std::endl;

        /* Custom TimeStamp in 24H time format, current week, seconds and milliseconds */
        /* TODO: format either should be followed by some specifier or text should be somehow separated */
        Timestamp timestamp2 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::CUSTOM).
                                                             SetPattern("Week w dd-MM-yyyy HH:mm:ss.SSS").
                                                             SetTimeFormat(Timestamp::TimeFormat::TIME_24_H).
                                                             Build();
        std::cout << "Custom TimeStamp in 24H time format, current week, seconds and milliseconds = " << timestamp2.Get().c_str() << std::endl;

        /* Default custom TimeStamp */
        Timestamp timestamp3 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::CUSTOM).Build();
        std::cout << "Default custom TimeStamp = " << timestamp3.Get().c_str() << std::endl;


        /* Pre-defined Year Month Day format, with seconds, milliseconds and offset */
        Timestamp timestamp4 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::YEAR_MONTH_DAY).
                                                             AddSeconds().
                                                             AddMilliseconds().
                                                             AddUtcOffset().
                                                             Build();
        std::cout << "Pre-defined Year Month Day format, with seconds, milliseconds and offset = " << timestamp4.Get().c_str() << std::endl;

        /* Month Day Year, Date only with Dash separator */
        Timestamp timestamp5 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::MONTH_DAY_YEAR).
                                                             SetTimeDateAppearance(Timestamp::TimeDateAppearance::DATE_ONLY).
                                                             SetDateSeparator(Timestamp::DateSeparator::DASH).
                                                             Build();
        std::cout << "Month Day Year, Date only with Dash separator = " << timestamp5.Get().c_str() << std::endl;

        /* Default timestamp */
        Timestamp timestamp6 = Timestamp::TimestampBuilder().Build();
        std::cout << "Default timestamp = " << timestamp6.Get().c_str() << std::endl;
}
