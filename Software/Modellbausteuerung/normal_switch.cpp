// 
// 
// 

#include "normal_switch.h"

Normal_switch_class::Normal_switch_class(int pin, int power, bool inverted, bool memory, int lower_limit, int upper_limit) : Switch_class(pin, power, inverted)
{
	this->lower_limit_ = lower_limit;
	this->upper_limit_ = upper_limit;
	this->triggered_ =	false;
	this->memory_ = memory;

}

void Normal_switch_class::init()
{
}

bool Normal_switch_class::check(int value)
{
	if (!memory_)
	{
		if (active_ == false && value >= lower_limit_ && value <= upper_limit_) { //Schalter soll schalten
			activate(); //Schalter aktivieren
		}
		else if (active_ == true && (value < lower_limit_ || value > upper_limit_)) { //Schalter ist im aktiven Zustand und muss deaktiviert werden
			deactivate(); //Schalter deaktivieren
		}
	}
	else
	{
		if (triggered_ == false && value >= lower_limit_ && value <= upper_limit_) //Schalter hat noch nicht ausgelöst und soll schalten
		{
			triggered_ = true;
			activate_memory(); //Schalte
		}
		else if (triggered_ == true && (value < lower_limit_ || value > upper_limit_)) //Schalter wurde ausgelöst und zurückgesetzt
		{
			triggered_ = false; //Schalter wieder auslösbar
		}
	}
	
	return active_; //Rückgabe des aktuellen Zustandes
}

void Normal_switch_class::activate()
{
	if (power_ > 0 && digitalPinHasPWM(pin_)) { //Es wurde Leuchtstärke angegeben und Pin ist PWM fähig
		if (!inverted_) //Nicht invertiert
		{
			analogWrite(pin_, power_); //PWM auf PIN ausgeben
		}
		else
		{
			analogWrite(pin_, 255 - power_); //Invertiertes PWM auf PIN ausgeben
		}
	}
	else {
		digitalWrite(pin_, HIGH^inverted_); //PIN als digitalen Ausgang schalten
	}
	active_ = true; //Zustand des Schalter ist: AKTIV
}

void Normal_switch_class::deactivate()
{
	if (power_ > 0 && digitalPinHasPWM(pin_)) { //Es wurde Leuchtstärke angegeben und Pin ist PWM fähig
		if (!inverted_) //Nicht invertiert
		{
			analogWrite(pin_, 0); //Kein PWM ausgeben
		}
		else
		{
			analogWrite(pin_, 255); //Maximales PWM ausgeben
		}

	}
	else {
		digitalWrite(pin_, LOW^inverted_); //PIN als digitalen Ausgang schalten
	}
	active_ = false; //Zustand des Schalter ist: INAKTIV
}

void Normal_switch_class::activate_memory()
{
		if (active_ == false)
		{
			activate();
		}
		else if (active_ == true)
		{
			deactivate();
		}
}
