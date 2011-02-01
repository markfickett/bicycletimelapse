#include "NikonRemote.h"

//shutter sequence (on,off,on,off ... in microsecond)
unsigned long sequence[] = {
	2000,27830,390,1580,410,3580,400,
	63200,
	2000,27830,390,1580,410,3580,400,0};
const int seq_l = sizeof(sequence)/sizeof(unsigned long);

NikonRemote::NikonRemote(int irPin, int statusPin)
	: pinStatus(statusPin), pinIR(irPin) {};

void NikonRemote::send()
{
	int i;
	digitalWrite(pinStatus, HIGH);
	for(i=0; i < seq_l; i++)
	{
		oscillate(pinIR, sequence[i], i%2==0);
	}
	digitalWrite(pinStatus, LOW);
}
 
void NikonRemote::oscillate(int pin, unsigned long n, int shine)
{
	int ir_status = 0;
	while(n > 0)
	{
		n--;
		delayMicroseconds(oscd);
		ir_status  =  !ir_status; 
		digitalWrite(pin,  ir_status && shine);  
	}
}
 
void NikonRemote::setup()
{
	int min=1, max=100, i;
	int last_oscd=0;
	unsigned long before, intervalle;
	oscd=max;

	pinMode(pinStatus, OUTPUT);
	pinMode(pinIR, OUTPUT);

	//this "while" will process the best "oscd"
	while(last_oscd!=oscd){
		last_oscd=oscd;
		oscd=(min+max)>>1;

		before=millis();
		oscillate(pinStatus, FREQ, 1);
		intervalle=millis()-before;

		if(intervalle >= 1000) max=oscd;
		else min=oscd;

	}

	// Rewrite the sequence array, replacing all microsecond values
	// with by the number of oscillations.
	for(i = 0; i < seq_l; i++)
	{
		sequence[i] = (sequence[i]*FREQ) / (intervalle * 1000);
	}
}
