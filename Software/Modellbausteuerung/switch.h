// switch.h

#ifndef _SWITCH_h
#define _SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Switch_class
{
 protected:
	 bool active_; //Status des Schalters: TRUE wenn aktiv, FALSE wenn inaktiv
	 int pin_; //Ausgang der geschaltet werden soll
	 bool inverted_; //Invertiert die Ausgänge bei TRUE;
	 int power_; //PWM Wert

 public:
	 Switch_class();
	Switch_class(int pin,int power, bool inverted);
	virtual void init()=0;
	virtual bool check(int value)=0;
	bool get_active_status();
	int get_pin();
};


#endif

