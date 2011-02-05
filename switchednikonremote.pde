/**
 * Send a Nikon IR remote signal when a (Hall effect sensor) switch is closed.
 * This is to take a photo each time a bicycle wheel completes a revolution
 * (or every few revolutions).
 */

#include "HallEffectSensor.h"
#include "NikonRemote.h"

// The reed switch is connected between this analog pin and ground,
//	in series with a 10K ohm resistor. NEXT
#define PIN_SWITCH		12

// The IR LED has its cathode (positive, longer lead) connected to this pin,
// and its anode (negative, shorter, flat-side lead) connected to ground. It is
// in series with an 82 Ohm resistor (based on a 50mA / 1.5V rating).
#define PIN_LED_IR		11

// The built-in status LED is on this pin.
#define PIN_LED_STATUS		13

// Send the remote signal every SEND_FREQUENCY times the sensor is triggered.
#define SEND_FREQUENCY		3

// Blink when the remote signal is being sent for its duration;
// also blink for STATUS_BLINK_DELAY milliseconds otherwise when triggered.
#define STATUS_BLINK_DELAY	50

HallEffectSensor hallEffectSensor(PIN_SWITCH);
NikonRemote remote(PIN_LED_IR);

unsigned int sensorTriggers;

void setup()
{
	hallEffectSensor.setup();
	remote.setup();
	sensorTriggers = 0;
	pinMode(PIN_LED_STATUS, OUTPUT);
}

void loop()
{
	hallEffectSensor.check();
	if (hallEffectSensor.wasTriggered())
	{
		sensorTriggers++;
		digitalWrite(PIN_LED_STATUS, HIGH);
		if (sensorTriggers >= SEND_FREQUENCY)
		{
			remote.send();
			sensorTriggers = 0;
		}
		else
		{
			delay(STATUS_BLINK_DELAY);
		}
		digitalWrite(PIN_LED_STATUS, LOW);
	}
}

