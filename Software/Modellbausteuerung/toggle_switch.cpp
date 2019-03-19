// 
// 
// 

#include "toggle_switch.h"

Toggle_switch_class::Toggle_switch_class(int pin, int power, bool inverted, bool memory, int lower_limit, int upper_limit, int time) : Switch_class(pin, power, inverted)
{
	this->lower_limit_ = lower_limit;
	this->upper_limit_ = upper_limit;
	this->wait_time_ = time;
	this->state_ = !inverted;
	this->memory_ = memory;
	this->test = false;
}

bool Toggle_switch_class::check(int value)
{
	if (!memory_) {
		if (value >= lower_limit_ && value <= upper_limit_) {
			if (millis() - start_time_ > wait_time_) {
				state_ = !state_;
				digitalWrite(pin_, state_);
				start_time_ = millis();
			}
			active_ = true;
		}
		else {
			if (active_ == true)
			{
				state_ = inverted_;
				digitalWrite(pin_, state_);
				active_ = false;
			}	
		}
	}
	else
	{
		if ((triggered_ == false) && (value >= lower_limit_ && value <= upper_limit_)) {
			triggered_ = true;
			active_ = !active_;
		}
		else if ((triggered_ == true) && (value < lower_limit_ || value > upper_limit_)) {
			triggered_ = false;
		}
		if (active_ == true)
		{
			test = false;
			if (millis() - start_time_ > wait_time_) {
				state_ = !state_;
				digitalWrite(pin_, state_);
				start_time_ = millis();
			}
		}
		else
		{
			if (test==false)
			{
				state_ = inverted_;
				digitalWrite(pin_, state_);
				test = true;
			}
			
		}
	}
	return active_;
}

void Toggle_switch_class::init()
{
}
