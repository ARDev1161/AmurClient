#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../../modules/registers/hc165/hc165.h"

class MockSettings : public RegisterSettings {
public:
    MOCK_METHOD(uint8_t, getClockPin, (), (override));
    MOCK_METHOD(uint8_t, getDataPin, (), (override));
    MOCK_METHOD(uint8_t, getLatchPin, (), (override));
};

class Hc165Test : public testing::Test {
protected:
    MockSettings mockSettings;
    HC165 inReg{&mockSettings};
};

TEST_F(Hc165Test, LoadRegisterTest) {
    EXPECT_CALL(mockSettings, getLatchPin()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(mockSettings, getDataPin()).WillRepeatedly(testing::Return(2));

    EXPECT_CALL(mockSettings, getClockPin())
        .WillOnce(testing::Return(3))
        .WillOnce(testing::Return(4))
        .WillOnce(testing::Return(5))
        .WillOnce(testing::Return(6))
        .WillOnce(testing::Return(7))
        .WillOnce(testing::Return(8))
        .WillOnce(testing::Return(9))
        .WillOnce(testing::Return(10));

    EXPECT_CALL(mockSettings, getClockPin()).Times(8);

    EXPECT_CALL(mockSettings, getDataPin()).Times(8);

    EXPECT_CALL(mockSettings, getLatchPin()).Times(8);

    EXPECT_NO_THROW(inReg.loadRegister());
}

TEST_F(Hc165Test, ReadByteTest) {
    EXPECT_CALL(mockSettings, getDataPin()).WillRepeatedly(testing::Return(2));

    EXPECT_CALL(mockSettings, getClockPin())
        .WillOnce(testing::Return(3))
        .WillOnce(testing::Return(4))
        .WillOnce(testing::Return(5))
        .WillOnce(testing::Return(6))
        .WillOnce(testing::Return(7))
        .WillOnce(testing::Return(8))
        .WillOnce(testing::Return(9))
        .WillOnce(testing::Return(10));

    EXPECT_CALL(mockSettings, getLatchPin()).WillRepeatedly(testing::Return(1));

    EXPECT_CALL(mockSettings, getDataPin()).Times(8);

    EXPECT_CALL(mockSettings, getClockPin()).Times(8);

    EXPECT_CALL(mockSettings, getLatchPin()).Times(8);

    EXPECT_NO_THROW(inReg.readByte());
}

TEST_F(Hc165Test, DisableClockTest) {
    EXPECT_CALL(mockSettings, getClockPin()).WillRepeatedly(testing::Return(3));

    EXPECT_NO_THROW(inReg.disableClock());
}

TEST_F(Hc165Test, EnableClockTest) {
    EXPECT_CALL(mockSettings, getClockPin()).WillRepeatedly(testing::Return(3));

    EXPECT_NO_THROW(inReg.enableClock());
}

