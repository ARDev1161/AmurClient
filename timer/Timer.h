#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_MONOTONIC
#define SIG SIGRTMIN


/// Enumeration of CppTimer types
typedef enum TimerType{
    PERIODIC, ///< Periodic timer type
    ONESHOT   ///< Oneshot timer type
}TimerType;

/*!
  \brief Timer class, wrapper around the POSIX per-process timer.

  Timer class which repeatedly fires. It's wrapper around the POSIX per-process timer.
*/
class Timer {

public:
	Timer();
    virtual ~Timer();

    virtual void start(long nanosecs, TimerType type = PERIODIC);
    virtual void stop();

protected:
    /*!
     Abstract function which needs to be implemented by the children.
     This is called every time the timer fires.
    */
	virtual void timerEvent() = 0;

private:
	timer_t timerid = 0;
    struct sigevent sigEvent;
    struct sigaction sigAction;
    struct itimerspec iTimerSpec;
		
    static void handler( [[maybe_unused]] int sig, siginfo_t *si, [[maybe_unused]] void *uc ) {
        (reinterpret_cast<Timer *> (si->si_value.sival_ptr))->timerEvent();
	}
};


#endif
