/**
 * Send a Nikon IR remote signal when a (Reed) switch is closed.
 * This is to take a photo each time a bicycle wheel completes a revolution.
 */

// The reed switch is connected between this pin and ground.
#define PIN_SWITCH		5

// The IR LED has its cathode (positive, longer lead) connected to this pin,
// and its anode (negative, shorter, flat-side lead) connected to ground. It is
// in series with an 82 Ohm resistor (based on a 50mA / 1.5V rating).
#define PIN_LED_IR		4

// The built-in status LED is on this pin.
#define PIN_LED_STATUS		13

void setup()
{
	// Set up the pins as input or output, appropriately.
	pinMode(PIN_SWITCH, INPUT);
	pinMode(PIN_LED_IR, OUTPUT);
	pinMode(PIN_LED_STATUS, OUTPUT);

	// Set the switch's pin to be HIGH by default
	// (enable the internal pull-up resistor).
	digitalWrite(PIN_SWITCH, HIGH);
}

void loop()
{
	// When the switch is closed, the INPUT pin will be pulled low.
	bool isClosed = digitalRead(PIN_SWITCH) == LOW;

	// Turn on the status LED when the switch is closed.
	digitalWrite(PIN_LED_STATUS, isClosed ? HIGH : LOW);
}
