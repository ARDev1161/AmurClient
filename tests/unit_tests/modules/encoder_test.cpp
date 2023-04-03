#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../modules/encoder.h"

// Mock класс для эмуляции ввода с пина
class MockInputPin {
public:
    MOCK_METHOD(bool, read, ());
};

// Mock класс для эмуляции вывода на пин
class MockOutputPin {
public:
    MOCK_METHOD(void, write, (bool value));
};

// Тесты класса Encoder
// Тест проверяет, что позиция Encoder изначально равна 0
TEST(EncoderTest, TestInitialPositionIsZero) {
    // Создаем mock-объекты для пинов
    MockInputPin mock_pin1, mock_pin2;
    // Устанавливаем ожидания для mock-объектов
    EXPECT_CALL(mock_pin1, read()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mock_pin2, read()).WillRepeatedly(::testing::Return(false));

    // Создаем объект Encoder
    Encoder encoder(&mock_pin1, &mock_pin2);

    // Проверяем, что позиция изначально равна 0
    EXPECT_EQ(encoder.getPosition(), 0);
}

// Тест проверяет, что позиция Encoder обновляется правильно при движении вперед
TEST(EncoderTest, TestUpdatePositionForward) {
// Создаем mock-объекты для пинов
    MockInputPin mock_pin1, mock_pin2;
    // Устанавливаем ожидания для mock-объектов
    EXPECT_CALL(mock_pin1, read())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(true))
        .WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mock_pin2, read())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true))
        .WillRepeatedly(::testing::Return(false));

    // Создаем объект Encoder
    Encoder encoder(&mock_pin1, &mock_pin2);

    // Обновляем позицию и проверяем, что она равна 1
    encoder.updatePosition();
    EXPECT_EQ(encoder.getPosition(), 1);
    // Обновляем позицию еще раз и проверяем, что она равна 2
    encoder.updatePosition();
    EXPECT_EQ(encoder.getPosition(), 2);
}

// Тест проверяет, что позиция Encoder обновляется правильно при движении назад
TEST(EncoderTest, TestUpdatePositionBackward) {
    // Создаем mock-объекты для пинов
    MockInputPin mock_pin1, mock_pin2;
    // Устанавливаем ожидания для mock-объектов
    EXPECT_CALL(mock_pin1, read())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true))
        .WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mock_pin2, read())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(true))
        .WillRepeatedly(::testing::Return(false));

    // Создаем объект Encoder
    Encoder encoder(&mock_pin1, &mock_pin2);
    encoder.updatePosition();
    EXPECT_EQ(encoder.getPosition(), -1);
    encoder.updatePosition();
    EXPECT_EQ(encoder.getPosition(), -2);
}

// Тест проверяет, что позиция остается неизменной при отсутствии вращения энкодера
TEST(EncoderTest, TestUpdatePositionNoChange) {
// Создаем mock-объекты для пинов
    MockInputPin mock_pin1, mock_pin2;
    // Устанавливаем ожидания для mock-объектов
    EXPECT_CALL(mock_pin1, read()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mock_pin2, read()).WillRepeatedly(::testing::Return(false));

    // Создаем объект Encoder
    Encoder encoder(&mock_pin1, &mock_pin2);
    encoder.updatePosition();
    EXPECT_EQ(encoder.getPosition(), 0);
}

// Тест проверяет, что метод enable() включает пины энкодера, через моки объекты mock_pin1 и mock_pin2
TEST(EncoderTest, TestEnableDisable) {
    // Создаем mock-объекты для пинов
    MockOutputPin mock_pin1, mock_pin2;
    // Устанавливаем ожидания для mock-объектов
    EXPECT_CALL(mock_pin1, write(true));
    EXPECT_CALL(mock_pin2, write(true));

    // Создаем объект Encoder
    Encoder encoder(&mock_pin1, &mock_pin2);
    encoder.enable();
}

TEST(EncoderTest, TestDisable) {
// Создаем mock-объекты для пинов
    MockOutputPin mock_pin1, mock_pin2;
    // Устанавливаем ожидания для mock-объектов
    EXPECT_CALL(mock_pin1, write(false));
    EXPECT_CALL(mock_pin2, write(false));

    // Создаем объект Encoder
    Encoder encoder(&mock_pin1, &mock_pin2);
    encoder.disable();
}
