#ifndef TS_STAMP_H_
#define TS_STAMP_H_

#include <cstring>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <sstream>
#include <iomanip>

using PairIntString = std::pair<int, std::string>;

class AuxStamp {
public:
    static std::string PlaceTwoDigits(const int value);
    static std::string PlaceThreeDigits(const int value);
    static std::string PlaceFourDigits(const int value);
};

#endif /* TS_STAMP_H_ */
