// change_switch.h

#ifndef _CHANGE_SWITCH_h
#define _CHANGE_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "switch.h"

class Change_switch_class : public Switch_class
{
 private:
	 int limit_;
	 unsigned long wait_time_;
	 int last_value_;
	 unsigned long start_time_;

 public:
	 Change_switch_class(int pin, int power, bool inverted, unsigned long time);

	 // Geerbt über Switch_class
	 virtual bool check(int value) override;
	 virtual void init() override;
};

#endif

