/**
 * Send a Nikon IR remote signal when a (Reed) switch is closed.
 * This is to take a photo each time a bicycle wheel completes a revolution.
 */

#include "MomentaryButton.h"
#include "NikonRemote.h"

// The reed switch is connected between this pin and ground.
#define PIN_SWITCH		5

// The IR LED has its cathode (positive, longer lead) connected to this pin,
// and its anode (negative, shorter, flat-side lead) connected to ground. It is
// in series with an 82 Ohm resistor (based on a 50mA / 1.5V rating).
#define PIN_LED_IR		4

// The built-in status LED is on this pin.
#define PIN_LED_STATUS		13

MomentaryButton reedSwitch(PIN_SWITCH);
NikonRemote remote(PIN_LED_IR, PIN_LED_STATUS);

void setup()
{
	reedSwitch.setup();
	remote.setup();
}

void loop()
{
	reedSwitch.check();
	if (reedSwitch.wasClicked() || reedSwitch.wasHeld())
	{
		remote.send();
	}
}

