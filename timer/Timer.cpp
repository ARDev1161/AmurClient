#include "Timer.h"

/*!
   Creates an instance of the timer and connects the signal handler to the timer.
*/
Timer::Timer() {
}

/*!
  Destructor disarms the timer, deletes it and disconnect the signal handler.
*/
Timer::~Timer() {
    stop();
}

/*!
  Starts the timer. The timer fires first after the specified time in nanoseconds and then at that interval in PERIODIC mode.
  In ONESHOT mode the timer fires once after the specified time in nanoseconds.
*/
void Timer::start(std::chrono::milliseconds delay, bool asynchronous) {
    if (asynchronous) {
      std::thread([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        this->timerEvent();
      }).detach();
    }
    else {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      this->timerEvent();
    }
}

/*!
  Stops the timer by disarming it. It can be re-started with start().
*/
void Timer::stop() {
}
