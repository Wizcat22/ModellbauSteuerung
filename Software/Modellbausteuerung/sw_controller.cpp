// 
// 
// 

#include "sw_controller.h"

void Controller_class::init()
{


}

Controller_class::Controller_class()
{
	counter_ = 0;
}

void Controller_class::add_normal_switch(int channel, int pin, int power, bool inverted, int lower_limit, int upper_limit)
{
	if(counter_<NUM_SWITCHES){
	
	channel_[counter_] = channel;
	switches_[counter_] = new Normal_switch_class(pin,power,inverted,false,lower_limit,upper_limit);
	counter_++;
	}
}

void Controller_class::add_memory_switch(int channel, int pin, int power, bool inverted, int lower_limit, int upper_limit)
{
	if (counter_<NUM_SWITCHES) {
	channel_[counter_] = channel;
	switches_[counter_] = new Normal_switch_class(pin, power, inverted, false, lower_limit,upper_limit);
	counter_++;
	}
}

void Controller_class::add_toggle_switch(int channel, int pin, int power, bool inverted, int lower_limit, int upper_limit, int time)
{
	if (counter_<NUM_SWITCHES) {
	channel_[counter_] = channel;
	switches_[counter_] = new Toggle_switch_class(pin, power, inverted, lower_limit,upper_limit,time);
	counter_++;
	}
}

void Controller_class::add_change_switch(int channel, int pin, int power, bool inverted, unsigned long time)
{
	if (counter_<NUM_SWITCHES) {
	channel_[counter_] = channel;
	switches_[counter_] = new Change_switch_class(pin,power,inverted,time);
	counter_++;
	}
}

void Controller_class::add_pwm_switch(int channel, int pin, bool inverted, double acceleration)
{
	if (counter_<NUM_SWITCHES) {
	channel_[counter_] = channel;
	switches_[counter_] = new Pwm_switch_class(pin, inverted, acceleration);
	counter_++;
	}
}

void Controller_class::check(int channel_data[20], int num_channel)
{

	for (int i = 0; i < counter_;i++) {

				Serial.println("DATEN");

				Serial.println(channel_data[i]);		
			
			//switches_[i]->check(channel_data[channel_[i]]);
		
	}

}

