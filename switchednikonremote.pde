/**
 * Send a Nikon IR remote signal when a (Reed) switch is closed.
 * This is to take a photo each time a bicycle wheel completes a revolution.
 */

#include "MomentaryButton.h"

// The reed switch is connected between this pin and ground.
#define PIN_SWITCH		5

// The IR LED has its cathode (positive, longer lead) connected to this pin,
// and its anode (negative, shorter, flat-side lead) connected to ground. It is
// in series with an 82 Ohm resistor (based on a 50mA / 1.5V rating).
#define PIN_LED_IR		4

// The built-in status LED is on this pin.
#define PIN_LED_STATUS		13

MomentaryButton reedSwitch(PIN_SWITCH);

void setup()
{
	// Set up the pins as input or output, appropriately.
	pinMode(PIN_LED_IR, OUTPUT);
	pinMode(PIN_LED_STATUS, OUTPUT);

	reedSwitch.setup();
}

void loop()
{
	reedSwitch.check();
	if (reedSwitch.wasClicked() || reedSwitch.wasHeld())
	{
		digitalWrite(PIN_LED_STATUS, HIGH);
		delay(200);
		digitalWrite(PIN_LED_STATUS, LOW);
	}
}
