#ifndef RAW_TEST_H_
#define RAW_TEST_H_

#include "unit_test.hh"
#include "ts_raw.hh"

class RawUt : public UnitTest {
private:
    const int kMaxDateSets = 1;
    const std::string TYPE = "Raw";
public:
    RawUt();
    const int run();
    const bool verifyCompilance(const std::string match, const std::string pattern) const;
    const std::string returnFileName() const;
};


#endif /* RAW_TEST_H_ */