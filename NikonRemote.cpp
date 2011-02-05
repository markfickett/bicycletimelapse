#include "NikonRemote.h"

// The built-in status LED is used when calibrating timings.
#ifndef PIN_LED_STATUS
#define PIN_LED_STATUS	13
#endif

// Define this to avoid recalibrating on setup.
// LilyPad Arduino ATmega328: 14, 962
//#define CALIBRATED_OSCD		14
//#define CALIBRATED_INTERVAL	962


//shutter sequence (on,off,on,off ... in microsecond)
unsigned long sequence[] = {
	2000,27830,390,1580,410,3580,400,
	63200,
	2000,27830,390,1580,410,3580,400,0};
const int seq_l = sizeof(sequence)/sizeof(unsigned long);

NikonRemote::NikonRemote(int irPin)
	: pinIR(irPin) {};

void NikonRemote::send()
{
	int i;
	for(i=0; i < seq_l; i++)
	{
		oscillate(pinIR, sequence[i], i%2==0);
	}
}
 
void NikonRemote::oscillate(int pin, unsigned long n, int shine)
{
	int ir_status = 0;
	while(n > 0)
	{
		n--;
		delayMicroseconds(oscd);
		ir_status = !ir_status; 
		digitalWrite(pin, ir_status && shine);  
	}
	// Avoid leaving the light on.
	if (ir_status && shine == HIGH)
	{
		digitalWrite(pin, LOW);
	}
}
 
void NikonRemote::setup()
{

	unsigned long interval;
	#ifdef CALIBRATED_OSCD
	oscd = CALIBRATED_OSCD;
	interval = CALIBRATED_INTERVAL;
	#else
	int min=1, max=100;
	int last_oscd = 0;
	unsigned long before;
	oscd = max;

	pinMode(PIN_LED_STATUS, OUTPUT);

	// Process the best "oscd". Do a binary search between "min" and "max"
	// for the value of "oscd" that results in a call to oscillate
	// taking the correct amount of time (for the calibration, oscillating
	// FREQ times should by definition take 1 second).
	while(last_oscd != oscd) // as long as still converging
	{
		last_oscd = oscd;
		oscd = (min+max) >> 1;

		before = millis();
		oscillate(PIN_LED_STATUS, FREQ, 1); // uses the current oscd
		interval = millis() - before;

		if (interval >= 1000) {
			max = oscd;
		} else {
			min = oscd;
		}

	}
	Serial.begin(28800);
	Serial.print("Calibrated oscd value: ");
	Serial.println(oscd);
	Serial.print("Calibrated interval value: ");
	Serial.println(interval);
	#endif

	// Rewrite the sequence array, replacing all microsecond values
	// with by the number of oscillations.
	for(int i = 0; i < seq_l; i++)
	{
		sequence[i] = (sequence[i]*FREQ) / (interval * 1000);
	}

	pinMode(pinIR, OUTPUT);
}
