 #include "hc595.h"
#include "gmock/gmock.h"

class HC595Mock : public HC595 {
public:
    MOCK_METHOD(void, writeByte, (unsigned char byte), (override));
    MOCK_METHOD(void, latchSignal, (), (override));
    MOCK_METHOD(void, enable, (), (override));
    MOCK_METHOD(void, disable, (), (override));
    MOCK_METHOD(void, reset, (), (override));
};
