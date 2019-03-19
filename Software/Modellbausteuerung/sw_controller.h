// switch_controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define NUM_SWITCHES 10

#include "switch.h"
#include "pwm_switch.h"
#include "normal_switch.h"
#include "change_switch.h"
#include "toggle_switch.h"

class Controller_class
{
 protected:
	 int counter_;
	 Switch_class* switches_[NUM_SWITCHES];
	 int channel_[10];

 public:
	void init();
	Controller_class();
	void add_normal_switch(int channel, int pin, int power, bool inverted, int lower_limit, int upper_limit);
	void add_memory_switch(int channel, int pin, int power, bool inverted, int lower_limit, int upper_limit);
	void add_toggle_switch(int channel, int pin, int power, bool inverted,bool memory, int lower_limit, int upper_limit, int time);
	void add_change_switch(int channel, int pin, int power, bool inverted, unsigned long time);
	void add_pwm_switch(int channel, int pin, bool inverted, double acceleration);
	void check(int channel_data[],int num_channel);
};

#endif

