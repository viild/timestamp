#include <stdio.h>
#include <wlc/timestamp/c_api.h>

int main()
{
        /* Custom TimeStamp in 12H time format and show full day of the week */
        timestamp_t timestamp = NewTimestampSpecific(CUSTOM, SLASH, TIME_12_H, LOCAL,
                                                     ALL, M_NONE, D_FULL, "E dd-MM-yyyy HH:mm a",
                                                     FALSE, FALSE, FALSE);
        printf("Custom TimeStamp in 12H time format and day of the week = %s\n", GetTimestamp(timestamp));
        FreeTimestamp(timestamp);

        /* Custom TimeStamp in 24H time format, current week, seconds and milliseconds */
        /* TODO: format either should be followed by some specifier or text should be somehow separated */
        timestamp_t timestamp2 = NewTimestampSpecific(CUSTOM, SLASH, TIME_24_H, LOCAL,
                                                      ALL, M_NONE, D_FULL, "Week w dd-MM-yyyy HH:mm:ss.SSS",
                                                      FALSE, FALSE, FALSE);
        printf("Custom TimeStamp in 24H time format, current week, seconds and milliseconds = %s\n", GetTimestamp(timestamp2));
        FreeTimestamp(timestamp2);

        /* Default custom TimeStamp */
        timestamp_t timestamp3 = NewTimestampSpecific(CUSTOM, SLASH, TIME_24_H, LOCAL,
                                                      ALL, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                      FALSE, FALSE, FALSE);
        printf("Default custom TimeStamp = %s\n", GetTimestamp(timestamp3));
        FreeTimestamp(timestamp3);


        /* Pre-defined Year Month Day format, with seconds, milliseconds and offset */
        timestamp_t timestamp4 = NewTimestampSpecific(YEAR_MONTH_DAY, SLASH, TIME_24_H, LOCAL,
                                                      ALL, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                      TRUE, TRUE, TRUE);
        printf("Pre-defined Year Month Day format, with seconds, milliseconds and offset = %s\n", GetTimestamp(timestamp4));
        FreeTimestamp(timestamp4);

        /* Month Day Year, Date only with Dash separator */
        timestamp_t timestamp5 = NewTimestampSpecific(MONTH_DAY_YEAR, DASH, TIME_24_H, LOCAL,
                                                      DATE_ONLY, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                      FALSE, FALSE, FALSE);
        printf("Month Day Year, Date only with Dash separator = %s\n", GetTimestamp(timestamp5));
        FreeTimestamp(timestamp5);

        /* Default timestamp */
        timestamp_t timestamp6 = NewTimestampSpecific(DAY_MONTH_YEAR, SLASH, TIME_24_H, LOCAL,
                                                      ALL, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                      FALSE, FALSE, FALSE);
        printf("Default timestamp = %s\n", GetTimestamp(timestamp6));
        FreeTimestamp(timestamp6);
}
