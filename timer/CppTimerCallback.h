#ifndef __CPP_TIMER_CALLBACK
#define __CPP_TIMER_CALLBACK
#include <stdio.h>
#include "CppTimer.h"
#include <unistd.h>


/*!
  \brief Timer callback wrapper for CppTimer class.

  Timer callback wrapper for CppTimer class.
*/
class CppTimerCallback : public CppTimer {

public:
    /*!
      \brief Runnable class for overloading run function.

      Runnable class exists for overloading run function.
    */
	class Runnable {
	public:
        /*!
          Overloadable timer event function for executing.
        */
		virtual void run() = 0;
	};

    /*!
      Registrate Runnable class in instance.
    */
	void registerEventRunnable(Runnable &h) {
		cppTimerEventRunnable = &h;
	}

    /*!
      Unregistrate Runnable class in instance.
    */
	void unregisterEventRunnable() {
		cppTimerEventRunnable = NULL;
	}

    /*!
      Timer event, execute function run.
    */
    void timerEvent() {
		if (cppTimerEventRunnable) {
			cppTimerEventRunnable->run();
		}
	}

private:
	Runnable* cppTimerEventRunnable = NULL;

};


#endif
