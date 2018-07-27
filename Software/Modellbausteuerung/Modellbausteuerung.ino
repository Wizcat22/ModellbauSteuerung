
#include "pwm_switch.h"
#include "normal_switch.h"
#include "change_switch.h"
#include "toggle_switch.h"
#include "switch.h"
#include "sw_controller.h"
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#define NUM_CHANNELS 20

#define CHANNEL_MAXIMUM 100
#define CHANNEL_MINIMUM -100

#define SLAVE_ID 11

signed char channel_data[NUM_CHANNELS]; //pulslängen
volatile byte pos;

#if SLAVE_ID==8

Switch_class * standlicht;
Switch_class * abblendlicht;
Switch_class * lenkung;
Switch_class * lenkung_2;
Switch_class * fernlicht;
Switch_class * servo_2;
Switch_class * fahrregler;
Switch_class * innenbeleuchtung;
Switch_class * blinker_rechts;
Switch_class * blinker_links;
Switch_class * tagfahrlicht;
Switch_class * nebellicht;
Switch_class * dachlampen;
Switch_class * positionslampen;


#endif // SLAVE_ID==8


#if SLAVE_ID==9

Switch_class * servo_0;
Switch_class * rueklicht;
Switch_class * servo_1;
Switch_class * servo_2;
//Switch_class * none0;
Switch_class * anhaengerkupplung;
Switch_class * servo_4;
Switch_class * bremslicht;
Switch_class * blinker_rechts;
Switch_class * blinker_links;
Switch_class * rueckfahrlicht;
Switch_class * nebelschlussleuchte;
Switch_class * rundumlicht;
//Switch_class * none3;

#endif // SLAVE_ID==9

#if SLAVE_ID==10

Switch_class * servo_0;
Switch_class * schalter_0;
Switch_class * servo_1;
Switch_class * servo_2;
Switch_class * schalter_1;
Switch_class * servo_3;
Switch_class * servo_4;
Switch_class * servo_5;
Switch_class * schalter_2;
Switch_class * schalter_3;
Switch_class * schalter_4;
Switch_class * schalter_5;
Switch_class * schalter_6;
Switch_class * schalter_7;

#endif // SLAVE_ID==10

#if SLAVE_ID==11

Switch_class * schalter_0;
Switch_class * schalter_1;
Switch_class * schalter_2;
Switch_class * schalter_3;
Switch_class * schalter_4;
Switch_class * schalter_5;
Switch_class * schalter_6;
Switch_class * schalter_7;
Switch_class * schalter_8;
Switch_class * schalter_9;
Switch_class * schalter_10;
Switch_class * schalter_11;
Switch_class * schalter_12;
Switch_class * schalter_13;

#endif // SLAVE_ID==11


void setup()
{
	Wire.begin(SLAVE_ID);                // starte I2C mit der Addresse 8
	Wire.onReceive(receiveEvent); // Funktion die bei eingehender I2C-Anfrage aufgerufen wird

#if SLAVE_ID==8
	//Normal_switch_class(int pin, int power, bool inverted, bool memory, int lower_limit, int upper_limit)
	standlicht = new Normal_switch_class(3,20,true,true,50,100);
	abblendlicht = new Normal_switch_class(4, 200, true,true, -100, -50);
	lenkung = new Pwm_switch_class(5,false,0.4);
	lenkung_2 = new Pwm_switch_class(6, false, 0.4);
	fernlicht = new Normal_switch_class(8,255,true,true,50,100);
	servo_2 = new Pwm_switch_class(9, false, 0.35);
	fahrregler = new Pwm_switch_class(10, false, 0.5);
	tagfahrlicht = new Normal_switch_class(11, 20, true, true, -100, -50);
	blinker_rechts = new Toggle_switch_class(12,255,true,50,100,500);
	blinker_links = new Toggle_switch_class(13, 255, true, -100, -50, 500);
	innenbeleuchtung = new Normal_switch_class(A0, 255, true, true, 50, 100);
	nebellicht = new Normal_switch_class(A1, 255, true, true, -100, -50);
	dachlampen = new Normal_switch_class(A2, 255, true, true, 50, 100);
	positionslampen = new Normal_switch_class(A3, 255, true, true, -100, -50);

#endif // SLAVE_ID==8

#if SLAVE_ID==9

	//servo_0 = new Pwm_switch_class(3,false,0.5);
	rueklicht = new Normal_switch_class(4,255,true,true,-100,-50);
	//servo_1 = new Pwm_switch_class(5,false,0.5);
	//servo_2 = new Pwm_switch_class(6,false,0.5);
	//none
	anhaengerkupplung = new Pwm_switch_class(9,false,0.5);
	//servo_4 = new Pwm_switch_class(10,false,0.5);
	bremslicht = new Change_switch_class(11,255,true,1000);
	blinker_rechts = new Toggle_switch_class(12,255,true,50,100,500);
	blinker_links = new Toggle_switch_class(13,255,true,-100,-50,500);
	rueckfahrlicht = new Normal_switch_class(A0,255,true,false,-100,-20);
	nebelschlussleuchte = new Normal_switch_class(A1,255,true,true,-100,-50);
	rundumlicht = new Normal_switch_class(A2,255,true,true,50,100);
	//none

#endif // SLAVE_ID==9

#if SLAVE_ID==10
	servo_0 = new Pwm_switch_class(3, false, 0.5);
	servo_1 = new Pwm_switch_class(5, false, 0.5);
	servo_2 = new Pwm_switch_class(6, false, 0.5);
	servo_3 = new Pwm_switch_class(9, false, 0.5);
	servo_4 = new Pwm_switch_class(10, false, 0.5);
	servo_5 = new Pwm_switch_class(11, false, 0.5);
	schalter_0 == new Normal_switch_class(4, 0, true, true, 50, 100);
	schalter_1 == new Normal_switch_class(8, 0, true, true, 50, 100);
	schalter_2 == new Normal_switch_class(12, 0, true, true, 50, 100);
	schalter_3 == new Normal_switch_class(13, 0, true, true, 50, 100);
	schalter_4 == new Normal_switch_class(A0, 0, true, true, 50, 100);
	schalter_5 == new Normal_switch_class(A1, 0, true, true, 50, 100);
	schalter_6 == new Normal_switch_class(A2, 0, true, true, 50, 100);
	schalter_7 == new Normal_switch_class(A3, 0, true, true, 50, 100);
#endif // SLAVE_ID==10

#if SLAVE_ID==11
	schalter_0 = new Normal_switch_class(3, 255, true, true, -100, -50);
	schalter_1 = new Normal_switch_class(4, 255, true, true, 50, 100);
	schalter_2 = new Normal_switch_class(5, 0, true, true, -100, -50);
	schalter_3 = new Normal_switch_class(6, 0, true, true, 50, 100);
	schalter_4 = new Normal_switch_class(8, 0, true, true, -100, -50);
	schalter_5 = new Normal_switch_class(9, 0, true, true, 50, 100);
	schalter_6 = new Normal_switch_class(10, 0, true, true, -100, -50);
	schalter_7 = new Normal_switch_class(11, 20, true, true, 50, 100);
	schalter_8 = new Normal_switch_class(12, 20, true, true, 50, 100);
	schalter_9 = new Normal_switch_class(13, 20, true, true, 50, 100);
	schalter_10 = new Normal_switch_class(A0, 20, true, true, 50, 100);
	schalter_11 = new Normal_switch_class(A1, 20, true, true, 50, 100);
	schalter_12 = new Normal_switch_class(A2, 20, true, true, 50, 100);
	schalter_13 = new Normal_switch_class(A3, 20, true, true, 50, 100);
#endif // SLAVE_ID==11


	//// turn on SPI in slave mode
	//SPCR |= bit(SPE);
	//// have to send on master in, *slave out*
	//pinMode(MISO, OUTPUT);

	//// get ready for an interrupt 
	//pos = 50;   // buffer empty

	//// now turn on interrupts
	//SPCR |= bit(SPIE);

	Serial.begin(9600);
}

void loop()
{

#if SLAVE_ID==8
	
	standlicht->check(channel_data[13 - 1]);
	abblendlicht->check(channel_data[13 - 1]);
	lenkung->check(channel_data[4 - 1]);
	lenkung_2->check(channel_data[3 - 1]);
	fernlicht->check(channel_data[14 - 1]);
	servo_2->check(channel_data[4 - 1]);
	fahrregler->check(channel_data[1 - 1]);
	tagfahrlicht->check(channel_data[15 - 1]);
	blinker_rechts->check(channel_data[4 - 1]);
	blinker_links->check(channel_data[4 - 1]);
	innenbeleuchtung->check(channel_data[15 - 1]);
	nebellicht->check(channel_data[14 - 1]);
	dachlampen->check(channel_data[16 - 1]);
	positionslampen->check(channel_data[16 - 1]);
	
#endif // SLAVE_ID==8


#if SLAVE_ID==9

	anhaengerkupplung->check(channel_data[18 - 1]);
	rueklicht->check(channel_data[13 - 1]);
	bremslicht->check(channel_data[1 - 1]);
	blinker_rechts->check(channel_data[4 - 1]);
	blinker_links->check(channel_data[4 - 1]);
	rueckfahrlicht->check(channel_data[1 - 1]);
	nebelschlussleuchte->check(channel_data[17 - 1]);
	rundumlicht->check(channel_data[17 - 1]);

#endif // SLAVE_ID==9

#if SLAVE_ID==10
	servo_0->check(channel_data[5 - 1]);
	servo_1->check(channel_data[6 - 1]);
	servo_2->check(channel_data[7 - 1]);
	servo_3->check(channel_data[9 - 1]);
	servo_4->check(channel_data[10 - 1]);
	servo_5->check(channel_data[11 - 1]);
#endif // SLAVE_ID==10

#if SLAVE_ID==11
	schalter_0->check(channel_data[2 - 1]);
	schalter_1->check(channel_data[2 - 1]);
	schalter_2->check(channel_data[12 - 1]);
	schalter_3->check(channel_data[12 - 1]);
	schalter_4->check(channel_data[19 - 1]);
	schalter_5->check(channel_data[19 - 1]);
	schalter_6->check(channel_data[20 - 1]);
	schalter_7->check(channel_data[20 - 1]);

	Serial.println(channel_data[2 - 1]);

#endif // SLAVE_ID==11
}

void receiveEvent(int howMany) {
	int count = 0;
	while (Wire.available()) { // loop through all bytes
		char c = Wire.read(); // receive byte

		if (count < NUM_CHANNELS) {
			channel_data[count] = c; //save channelvalue
		}
		count++;
	}
}

//ISR(SPI_STC_vect)
//{
//	char c = SPDR;
//
//	if (pos < (sizeof(channel_data))) {
//		channel_data[pos++] = c;
//	}
//		
//
//	if (c == '\n') {
//		pos = 0;
//	}
//		
//
//}