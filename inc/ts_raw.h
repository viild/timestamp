#ifndef RAW_H_
#define RAW_H_

#include "ts_stamp.h"

namespace timestamp {

class Raw : public Stamp {
private:
    const PairIntString BuildPattern() override;
public:
    Raw();
    const std::string Get() const;
};

} // namespace timestamp

#endif /* RAW_H_ */
