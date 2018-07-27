// normal_switch.h

#ifndef _NORMAL_SWITCH_h
#define _NORMAL_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "switch.h"

class Normal_switch_class : public Switch_class
{
 protected:
	 int lower_limit_;
	 int upper_limit_;
	 bool triggered_;
	 bool memory_;
	 void activate_memory();

 public:
	 Normal_switch_class(int pin, int power, bool inverted,bool memory, int lower_limit, int upper_limit);

	 void activate();
	 void deactivate();

	 // Geerbt über Switch_class
	 virtual bool check(int value) override;
	 virtual void init() override;
};


#endif

