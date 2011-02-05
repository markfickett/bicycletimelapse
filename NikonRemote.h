#pragma once
/**
 * This is a slight modification of Aurelien Antoine's code:
 *	http://ilpleut.be/code-nikonremote
 * the original header for which is reproduced below:
 *
 * @license	Creative commons: Attribution-Noncommercial-Share Alike 3.0
 *		(http://creativecommons.org/licenses/by-nc-sa/3.0/)
 * @author Aurelien ANTOINE
 * version 1
 * date 20081217
 */

#include "WProgram.h"

#define FREQ		38400	// IR frequence

class NikonRemote {
private:
	const int pinIR;
	int oscd; //oscd is a delay in microsecond used at each oscillation.
	void oscillate(int pin, unsigned long n, int shine);
public:
	NikonRemote(int irPin);
	void setup();
	void send();
 
};
