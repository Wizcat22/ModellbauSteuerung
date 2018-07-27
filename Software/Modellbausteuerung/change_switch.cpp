// 
// 
// 

#include "change_switch.h"

void Change_switch_class::init()
{
}

Change_switch_class::Change_switch_class(int pin, int power, bool inverted, unsigned long time) : Switch_class(pin, power, inverted)
{
	this->wait_time_ = time;
}

bool Change_switch_class::check(int value)
{	
	if ((abs(value)>0) && ((last_value_ - abs(value))>5)) {
		digitalWrite(pin_, HIGH^inverted_);
		start_time_ = millis();
		last_value_ = abs(value);
		active_ = true;
	}
	else {
		if ((millis() - start_time_) > wait_time_) {
			digitalWrite(pin_, LOW^inverted_);
			active_ = false;
		}
	}
	if (abs(value)>last_value_)
	{
		last_value_ = abs(value);
		digitalWrite(pin_, LOW^inverted_);
		active_ = false;
	}

	return active_;
}
