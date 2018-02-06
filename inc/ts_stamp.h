#ifndef TS_STAMP_H_
#define TS_STAMP_H_

#include <cstring>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <sstream>
#include <iomanip>

namespace timestamp {

using PairIntString = std::pair<int, std::string>;

class Stamp {
public:
    static std::string PlaceTwoDigits(const int value);
    static std::string PlaceThreeDigits(const int value);
    static std::string PlaceFourDigits(const int value);
};

} // namespace timestamp

#endif /* TS_STAMP_H_ */
