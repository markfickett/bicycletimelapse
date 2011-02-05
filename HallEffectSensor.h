#pragma once

#include "WProgram.h"

/**
 * Encapsulate tracking triggering of a Hall effect sensor's output pin,
 *	which is LOW when a magnet is close.
 *
 * After a call to check(), the sensor may report that it wasTriggered().
 * The next call to check() will not report on that previous event.
 */
class HallEffectSensor {
private:
	// Was this output LOW (closed) when last checked?
	boolean wasLow;
	// When was the output LOW?
	unsigned long lowTimeMillis;
	const int pin;
	boolean triggered; // At last check, was the sensor triggered?
public:
	HallEffectSensor(int inputPin);

	void setup();

	void check();

	boolean wasTriggered();
};

