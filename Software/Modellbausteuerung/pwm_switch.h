// pwm_switch.h

#ifndef _PWM_SWITCH_h
#define _PWM_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "switch.h"
#include <Servo.h>

class Pwm_switch_class : public Switch_class
{
 protected:
	 Servo servo_;
	 double servoPos_;
	 double acceleration_;

 public:
	 Pwm_switch_class(int pin, bool inverted, double acceleration);

	 // Geerbt über Switch_class
	 virtual bool check(int value) override;
	 virtual void init() override;
};

#endif

