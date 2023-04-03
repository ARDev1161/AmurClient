#include "hc595_mock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrictMock;

TEST(HC595Test, WriteByte) {
    // Arrange
    StrictMock<HC595Mock> hc595;
    unsigned char byte = 0xAB;
    EXPECT_CALL(hc595, writeByte(byte));

    // Act
    hc595.writeByte(byte);
}

TEST(HC595Test, LatchSignal) {
    // Arrange
    InSequence seq;
    StrictMock<HC595Mock> hc595;
    EXPECT_CALL(hc595, latchSignal());
    EXPECT_CALL(hc595, enable());

    // Act
    hc595.latchSignal();
}

TEST(HC595Test, Disable) {
    // Arrange
    StrictMock<HC595Mock> hc595;
    EXPECT_CALL(hc595, disable());

    // Act
    hc595.disable();
}

TEST(HC595Test, Enable) {
    // Arrange
    StrictMock<HC595Mock> hc595;
    EXPECT_CALL(hc595, enable());

    // Act
    hc595.enable();
}

TEST(HC595Test, Reset) {
    // Arrange
    StrictMock<HC595Mock> hc595;
    EXPECT_CALL(hc595, reset());

    // Act
    hc595.reset();
}

