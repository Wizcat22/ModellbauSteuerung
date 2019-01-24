//Deadband hinzufügen 
#define NUM_NORMAL_CHANNEL 12
#define NUM_MULTI_CHANNEL 8
#define NUM_CHANNEL (NUM_NORMAL_CHANNEL + NUM_MULTI_CHANNEL)
#define NUM_SYNC_PULSES 2
#define SYNC_TIME 2000
#define SYNC_WINDOW 40

#define CHANNEL_MAXIMUM 1895
#define CHANNEL_MEDIUM	1500
#define CHANNEL_MINIMUM 1105

//#define SPI_MODE
#define I2C_MODE
//#define TEST_MODE

//#define LOW_SPEED
#define HIGH_SPEED


#ifdef HIGH_SPEED

#ifdef SPI_MODE
#define SPI_FREQ 4000000
#endif // SPI_MODE

#ifdef I2C_MODE
#define I2C_FREQ 400000L
#endif // I2C_MODE


#endif // HIGH_SPEED

#ifdef LOW_SPEED

#ifdef SPI_MODE
#define SPI_FREQ 4000000L
#endif // SPI_MODE

#ifdef I2C_MODE
#define I2C_FREQ 100000L
#endif // I2C_MODE

#endif //LOW_SPEED


#define NUM_SLAVES 2

#define SERIAL_BAUD 19200

#include <Wire.h>
#include <SPI.h>


//#############- PWM Empfang -#############
const int pins[] = { 9,10,11,12,13,6,5,A0,4,A1,A2,A3 }; //channel pins Version 2
//const int pins[] = { 9,10,11,12,3,6,5,A0,4,A1,A2,A3 }; //channel pins Version 1
const int multiChannelPin = 7; //array position des multiChannel pins
int pulses[NUM_CHANNEL]; //pulslängen
int mSync = 0; //sync status der multiChannel
int mChannel = 0; //mChannel
int time = 0; //Gemessene Zeit eines Channels
//#############_ PWM Empfang _#############

//#############- I2C Sender -#############
#ifdef I2C_MODE
const uint8_t slaveAddr[] = { 8,9 }; //I2C-Addressen von allen slaves im bus

uint8_t slaveId = 0; //Slave der mit Daten versorgt werden soll
#endif // I2C_MODE
//#############_ I2C Sender _#############

void setup() {
	pinMode(8, OUTPUT);
#ifdef I2C_MODE
	Wire.begin(); //Starte I2C-Automat
	Wire.setClock(I2C_FREQ);
#endif // I2C_MODE

#ifdef SPI_MODE
	pinMode(10, OUTPUT); //Slave Select als Output
	SPI.begin(); //Initialisiere SPI
#endif // SPI_MODE

	Serial.begin(SERIAL_BAUD);
	initTimer(); //initialisiere Timer0 des AtMega328p

	/*for (int i = 0; i < NUM_CHANNEL; i++)
	{
		pulses[i] = 65+i;
	}*/

	//setze alle channel als Eingang
	for (int i = 0; i < NUM_CHANNEL; i++)
	{
		pinMode(pins[i], INPUT);
	}
	delay(1000);
}

void loop() {

	getChannelData();


#ifdef LOW_SPEED

#ifdef SPI_MODE
	sendData();
#endif // SPI_MODE

#ifdef I2C_MODE
	for (int i = 0; i < NUM_SLAVES; i++)
	{
		sendData();
	}
#endif // I2C_MODE

#ifdef TEST_MODE
	sendData();
#endif // TEST_MODE


#endif

}

//initialisiere Timer
void initTimer() {
	TCCR1A = 0;
	TCCR1B = 1;
	TCCR1C = 0;
}

void getChannelData() {

	//for (int i = 0; i < NUM_NORMAL_CHANNEL; i++)
	for (int i = 0; i < NUM_NORMAL_CHANNEL - 1; i++)
	{
		//Serial.println(i);
		if (i == 0)//Wenn der erste Channel abgefragt werden soll
		{
			while (digitalRead(pins[i]) == HIGH) {} //warte auf fallende Flanke (Ende laufendes Signal)

		}
		while (digitalRead(pins[i]) == LOW) {} //warte auf steigende Flanke (Anfang neues Signal)
		if (i == 0)
		{
			digitalWrite(8, HIGH);
		}
		startTimer(); //beginne Messung

		//######## ACHTUNG: Ausführungszeit in diesem Block darf die minimale Pulsdauer nicht überschreiten! #############
		if (i > 0)
		{
			if (time >= CHANNEL_MEDIUM) { //Wenn Channelausschlag Positiv
				pulses[i - 1] = 0.25* time - 375; //Berechne Position zwischen 0 & 100 und sende Wert
			}
			else {
				pulses[i - 1] = 0.22222222* time - 333.33333; //Berechne Position zwischen -100 & 0 und sende Wert
			}
		}
		if (i == multiChannelPin + 1)
		{
			if (time >= SYNC_TIME)
			{
				mSync++;
				mChannel = 0;
			}
			else
			{
				if (mSync == 2)
				{
					pulses[NUM_NORMAL_CHANNEL + mChannel] = pulses[i - 1];
					if (mChannel == (NUM_MULTI_CHANNEL - 1))
					{
						mSync = 0;
					}
					mChannel++;
				}
				else
				{
					mSync = 0;
					mChannel = 0;
				}
			}
		}

#ifdef HIGH_SPEED
		sendData();
#endif
		//########## ENDE ZEITKRITISCHER BLOCK ############
		while (digitalRead(pins[i]) == HIGH) {} //warte auf fallende Flanke des channels
		stopTimer(); //beende Messung
		time = (TCNT1 * (4096 / 65536.0)); //Pulslänge in us berechnen		
	}
	if (time >= CHANNEL_MEDIUM) { //Wenn Channelausschlag Positiv
		pulses[10] = 0.25* time - 375; //Berechne Position zwischen 0 & 100 und sende Wert
	}
	else {
		pulses[10] = 0.22222222* time - 333.33333; //Berechne Position zwischen -100 & 0 und sende Wert
	}
#ifdef HIGH_SPEED
	sendData();
#endif
	digitalWrite(8, LOW);
}

void startTimer() {
	TCNT1 = 0; //Timer zurücksetzen
	TCCR1B = 1; //Timer starten
}

void stopTimer() {
	TCCR1B = 0; //Timer stoppen
}


void sendData() {

#ifdef SPI_MODE
	SPI.beginTransaction(SPISettings(SPI_FREQ, MSBFIRST, SPI_MODE0));
	digitalWrite(10, LOW);
	for (int i = 0; i < NUM_CHANNEL - 10; i++) { //Durchlaufe alle Channels
		if (pulses[i] < -100) //Wenn kleiner als Minimum
		{
			pulses[i] = -100; //Auf Minimum begrenzen
		}
		if (pulses[i] > 100) //Wenn größer als Maximum
		{
			pulses[i] = 100; //Auf Maximum begrenzen
		}
		SPI.transfer(pulses[i]); //Sende Wert
		delayMicroseconds(50);
	}
	SPI.transfer('\n'); //Sende Wert
	delayMicroseconds(50);
	digitalWrite(10, HIGH);
	SPI.endTransaction();

#endif // SPI_MODE

#ifdef I2C_MODE
	Wire.beginTransmission(slaveAddr[slaveId]); // Bereite Übertragung vor
	for (int i = 0; i < NUM_CHANNEL; i++) { //Durchlaufe alle Channels
		if (pulses[i] < -100) //Wenn kleiner als Minimum
		{
			pulses[i] = -100; //Auf Minimum begrenzen
		}
		if (pulses[i] > 100) //Wenn größer als Maximum
		{
			pulses[i] = 100; //Auf Maximum begrenzen
		}
		Wire.write(pulses[i]); //Sende Wert
	}

	Wire.endTransmission();    // Starte Übertragung
	slaveId = (slaveId + 1) % NUM_SLAVES; //Setze Empfänger für nächsten Sendevorgang
#endif // I2C_MODE

#ifdef TEST_MODE
	Serial.println(pulses[10]);
#endif // TEST_MODE


}

