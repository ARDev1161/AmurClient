#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>
#include <thread>
#include <atomic>

#include "../../timer/Timer.h"

using namespace std::chrono_literals;
using namespace testing;

class MockTimerCallback {
public:
    MOCK_METHOD(void, call, ());
};

TEST(TimerTest, TestStartAndStop)
{
    std::chrono::milliseconds duration = 10ms;
    MockTimerCallback mockCallback;

    EXPECT_CALL(mockCallback, call()).Times(0);

    Timer timer(duration, std::bind(&MockTimerCallback::call, &mockCallback));

    timer.start();
    std::this_thread::sleep_for(duration * 5);
    timer.stop();

    std::this_thread::sleep_for(duration * 5);

    EXPECT_TRUE(Mock::VerifyAndClearExpectations(&mockCallback));
}

TEST(TimerTest, TestCallback)
{
    Duration duration = 10ms;
    MockTimerCallback mockCallback;

    EXPECT_CALL(mockCallback, call()).Times(AtLeast(2));

    Timer timer(duration, std::bind(&MockTimerCallback::call, &mockCallback));

    timer.start();
    std::this_thread::sleep_for(duration * 20);
    timer.stop();

    EXPECT_TRUE(Mock::VerifyAndClearExpectations(&mockCallback));
}

