#ifndef STAMP_H_
#define STAMP_H_

#include <cstring>
#include <string>
#include <cstdarg>
#include <cstdio>

namespace timestamp {

using PairIntString = std::pair<int, std::string>;

class Stamp {
private:
    const int kMaxValueSize = 256;
    std::string pattern;
protected:
    void SetPattern(const std::string & pattern);
    const std::string GetValue(const char * fmt, ...) const;
public:
    Stamp();
    virtual ~Stamp();
    virtual const PairIntString BuildPattern() = 0;
    const std::string GetPattern() const;
};

} // namespace timestamp

#endif /* STAMP_H_ */
