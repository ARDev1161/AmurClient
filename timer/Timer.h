#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

#include <chrono>
#include <functional>
#include <thread>

/*!
  \brief Timer class, wrapper around the POSIX per-process timer.

  Timer class which repeatedly fires. It's wrapper around the POSIX per-process timer.
*/
class Timer {
public:
	Timer();
    virtual ~Timer();

    virtual void start(std::chrono::milliseconds delay, bool asynchronous = true);
    virtual void stop();

protected:
    /*!
     Abstract function which needs to be implemented by the children.
     This is called every time the timer fires.
    */
	virtual void timerEvent() = 0;

private:
};

#endif
