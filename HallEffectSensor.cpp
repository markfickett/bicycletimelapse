#include "HallEffectSensor.h"

// Ignore closes that are less than MIN_REPEAT_INTERVAL milliseconds after
//	another close.
#define MIN_REPEAT_INTERVAL	50

HallEffectSensor::HallEffectSensor(int inputPin)
	: wasLow(false), pin(inputPin)
{}

void HallEffectSensor::setup()
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
	lowTimeMillis = millis();
}

void HallEffectSensor::check()
{
	unsigned long currentTimeMillis = millis();
	boolean isLow = (digitalRead(pin) == LOW);

	if (isLow
		&& (currentTimeMillis - lowTimeMillis < MIN_REPEAT_INTERVAL))
	{
		return;
	}

	if (isLow && !wasLow)
	{
		lowTimeMillis = currentTimeMillis;
	}

	triggered = !isLow && wasLow;
	wasLow = isLow;
}

boolean HallEffectSensor::wasTriggered() {
	return triggered;
}

