// 
// 
// 

#include "switch.h"

Switch_class::Switch_class()
{
}

Switch_class::Switch_class(int pin,int power, bool inverted)
{
	this->active_ = false;
	this->pin_ = pin;
	this->power_ = power;
	this->inverted_ = inverted;
	pinMode(this->pin_, OUTPUT);
	digitalWrite(this->pin_, LOW^this->inverted_);
}

bool Switch_class::get_active_status()
{
	return active_;
}

int Switch_class::get_pin()
{
	return pin_;
}
