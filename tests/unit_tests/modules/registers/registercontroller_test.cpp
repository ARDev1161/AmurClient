#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "registercontroller.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class MockHC165 : public HC165 {
public:
    MOCK_METHOD0(refreshInputData, void());
    MOCK_METHOD1(readByte, unsigned char(unsigned char));
};

class MockHC595 : public HC595 {
public:
    MOCK_METHOD1(writeByte, void(unsigned char));
    MOCK_METHOD0(latchSignal, void());
};

class RegisterControllerTest : public ::testing::Test {
protected:
    MockHC165* hc165;
    MockHC595* hc595;
    RegisterController* registerController;

    virtual void SetUp() {
        hc165 = new MockHC165();
        hc595 = new MockHC595();
        registerController = new RegisterController();
        registerController->setHC165(hc165);
        registerController->setHC595(hc595);
    }

    virtual void TearDown() {
        delete hc165;
        delete hc595;
        delete registerController;
    }
};

TEST_F(RegisterControllerTest, WriteByte_Invokes_HC595_WriteByte) {
    EXPECT_CALL(*hc595, writeByte(0xAA));
    registerController->writeByte(0xAA);
}

TEST_F(RegisterControllerTest, ReadByte_Invokes_HC165_ReadByte) {
    EXPECT_CALL(*hc165, readByte(1));
    registerController->readByte();
}

TEST_F(RegisterControllerTest, RefreshInputData_Invokes_HC165_RefreshInputData) {
    EXPECT_CALL(*hc165, refreshInputData());
    registerController->refreshInputData();
}

TEST_F(RegisterControllerTest, RefreshOutputData_Invokes_HC595_LatchSignal) {
    EXPECT_CALL(*hc595, latchSignal());
    registerController->refreshOutputData();
}

TEST_F(RegisterControllerTest, EnableRegisters_Invokes_HC165_Enable_And_HC595_Enable) {
    EXPECT_CALL(*hc165, enable());
    EXPECT_CALL(*hc595, enable());
    registerController->enableRegisters();
}

TEST_F(RegisterControllerTest, DisableRegisters_Invokes_HC165_Disable_And_HC595_Disable) {
    EXPECT_CALL(*hc165, disable());
    EXPECT_CALL(*hc595, disable());
    registerController->disableRegisters();
}

TEST_F(RegisterControllerTest, Constructor_With_Settings_Creates_HC165_And_HC595_With_Given_Settings) {
    RegisterSettings settings;
    HC165 hc165(&settings);
    HC595 hc595(&settings);
    EXPECT_CALL(*hc165.settings, set(1, 2, 3, 4));
    EXPECT_CALL(*hc595.settings, set(1, 2, 3, 4));
    RegisterController rc(&settings);
}

TEST_F(RegisterControllerTest, Constructor_Without_Settings_Creates_Default_Settings_And_HC165_And_HC595) {
    RegisterController rc;
    EXPECT_EQ(rc.getHC165().settings->serialDataPin, 4);
    EXPECT_EQ(rc.getHC595().settings->serialDataPin, 4);
}

