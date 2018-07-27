// toggle_switch.h

#ifndef _TOGGLE_SWITCH_h
#define _TOGGLE_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "switch.h"

class Toggle_switch_class : public Switch_class
{
 private:
	 int lower_limit_;
	 int upper_limit_;
	 unsigned long wait_time_;
	 unsigned long start_time_;
	 int state_;

 public:
	 Toggle_switch_class(int pin, int power, bool inverted, int lower_limit, int upper_limit, int time);

	 // Geerbt über Switch_class
	 virtual bool check(int value) override;
	 virtual void init() override;
};



#endif

