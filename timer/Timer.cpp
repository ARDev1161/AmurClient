#include "Timer.h"

/*!
   Creates an instance of the timer and connects the signal handler to the timer.
*/
Timer::Timer() {
	// We create a static handler catches the signal SIG
    sigAction.sa_flags = SA_SIGINFO;
    sigAction.sa_sigaction = handler;
    sigemptyset(&sigAction.sa_mask);
    if (sigaction(SIG, &sigAction, NULL) == -1)
		throw("Could not create signal handler");
	
	// Create the timer
    sigEvent.sigev_notify = SIGEV_SIGNAL;
    sigEvent.sigev_signo = SIG;
	// Cruical is that the signal carries the pointer to this class instance here
	// because the handler just handles anything that comes in!
    sigEvent.sigev_value.sival_ptr = this;
	// create the timer
    if (timer_create(CLOCKID, &sigEvent, &timerid) == -1)
		throw("Could not create timer");
};

/*!
  Starts the timer. The timer fires first after the specified time in nanoseconds and then at that interval in PERIODIC mode.
  In ONESHOT mode the timer fires once after the specified time in nanoseconds.
*/
void Timer::start(long nanosecs, TimerType type) {
	switch(type){
		case(PERIODIC):
			//starts after specified period of nanoseconds
            iTimerSpec.it_value.tv_sec = nanosecs / 1000000000;
            iTimerSpec.it_value.tv_nsec = nanosecs % 1000000000;
            iTimerSpec.it_interval.tv_sec = nanosecs / 1000000000;
            iTimerSpec.it_interval.tv_nsec = nanosecs % 1000000000;
			break;
		case(ONESHOT):
			//fires once after specified period of nanoseconds
            iTimerSpec.it_value.tv_sec = nanosecs / 1000000000;
            iTimerSpec.it_value.tv_nsec = nanosecs % 1000000000;
            iTimerSpec.it_interval.tv_sec = 0;
            iTimerSpec.it_interval.tv_nsec = 0;
			break;
	}
    if (timer_settime(timerid, 0, &iTimerSpec, NULL) == -1)
		throw("Could not start timer");
}

/*!
  Stops the timer by disarming it. It can be re-started with start().
*/
void Timer::stop() {
	// disarm
	struct itimerspec itsnew;
	itsnew.it_value.tv_sec = 0;
	itsnew.it_value.tv_nsec = 0;
	itsnew.it_interval.tv_sec = 0;
	itsnew.it_interval.tv_nsec = 0;
    timer_settime(timerid, 0, &itsnew, &iTimerSpec);
}

/*!
  Destructor disarms the timer, deletes it and disconnect the signal handler.
*/
Timer::~Timer() {
	stop();
	// delete the timer
	timer_delete(timerid);
	// default action for signal handling
	signal(SIG, SIG_IGN);
}
