#ifndef TS_RAW_H_
#define TS_RAW_H_

#include "ts_stamp.hh"

namespace timestamp {

class Raw {
public:
    const std::string Get() const;
};

} // namespace timestamp

#endif /* TS_RAW_H_ */
