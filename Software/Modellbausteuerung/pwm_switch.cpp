// 
// 
// 

#include "pwm_switch.h"

Pwm_switch_class::Pwm_switch_class(int pin, bool inverted, double acceleration) : Switch_class(pin, 0, inverted)
{
	Servo();
	servo_.attach(pin);
	this->acceleration_ = acceleration;
	
}

bool Pwm_switch_class::check(int value)
{	
	
	servoPos_ += acceleration_ * (value - servoPos_);
	servo_.write(map(servoPos_, -100, 100, 0, 180));

	
	return true;
}

void Pwm_switch_class::init()
{
}
