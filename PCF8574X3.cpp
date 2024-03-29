#include "PCF8574X3.h"

PCF8574X3::PCF8574X3()
{}

PCF8574X3::~PCF8574X3()
{}

void PCF8574X3::init(bool showLogPinModeExpander, bool showLogDigitalWriteExpander, bool showLogDigitalReadExpander)
{
	_showLogPinModeExpander = showLogPinModeExpander;
	_showLogDigitalWriteExpander = showLogDigitalWriteExpander;
	_showLogDigitalReadExpander = showLogDigitalReadExpander;
}

void PCF8574X3::init(int pin_digital_INT_signal, bool showLogPinModeExpander, bool showLogDigitalWriteExpander, bool showLogDigitalReadExpander)
{
	_showLogPinModeExpander = showLogPinModeExpander;
	_showLogDigitalWriteExpander = showLogDigitalWriteExpander;
	_showLogDigitalReadExpander = showLogDigitalReadExpander;
	init(pin_digital_INT_signal);
}

void PCF8574X3::init()
{
	expander_x3_1.begin(0x20);
	expander_x3_2.begin(0x21);
	expander_x3_3.begin(0x22);
}

void PCF8574X3::init(int pin_digital_INT_signal)
{
	expander_x3_1.begin(0x20);
	expander_x3_2.begin(0x21);
	expander_x3_3.begin(0x22);

	pinMode(pin_digital_INT_signal, INPUT);
	digitalWrite(pin_digital_INT_signal, HIGH);
}

//Configures the specified pin to act as an input or output.
void PCF8574X3::pinModeExpander(int pin, MODE mode)
{
	if (pin < 0 || pin > 23)
	{
		return;
	}

	setDevice(pin);
	if (expander == nullptr)
	{
		Serial.println("ERROR *ptr_expander in pinModeExpander(int pin, MODE mode)");
		return;
	}

	if (_showLogPinModeExpander)
	{
		Serial.print("pinModeExpander(");
		Serial.print(getPin(pin));
		Serial.print(", ");
		Serial.print((mode == INPUT_MODE ? "INPUT" : "OUTPUT"));
		Serial.println(")");
	}

	expander->pinMode(getPin(pin), (mode == INPUT_MODE ? INPUT : OUTPUT));

}

//They set the digital input low by default "LOW"
void PCF8574X3::pullDownExpander(int pin)
{
	if (pin < 0 || pin > 23)
	{
		return;
	}

	setDevice(pin);
	if (expander == nullptr)
	{
		Serial.println("ERROR *ptr_expander in pullDownExpander(int pin)");
		return;
	}

	expander->pullDown(getPin(pin));
}

//They set the digital input to a high state by default "HIGH"
void PCF8574X3::pullUpExpander(int pin)
{
	if (pin < 0 || pin > 23)
	{
		return;
	}

	setDevice(pin);
	if (expander == nullptr)
	{
		Serial.println("ERROR *ptr_expander in pullDownExpander(int pin)");
		return;
	}

	expander->pullUp(getPin(pin));
}

//Sets the state pin to low or high
void PCF8574X3::digitalWriteExpander(int pin, STATE state)
{
	if (pin < 0 || pin > 23)
	{
		return;
	}

	setDevice(pin);
	if (expander == nullptr)
	{
		Serial.println("ERROR *ptr_expander in digitalWriteExpander(int pin, STATE state)");
		return;
	}

	if (_showLogDigitalWriteExpander)
	{
		Serial.print("digitalWriteExpander(");
		Serial.print(getPin(pin));
		Serial.print(", ");
		Serial.print((state == LOW_STATE ? "LOW" : "HIGH"));
		Serial.println(")");
	}

	expander->digitalWrite(getPin(pin), (state == LOW_STATE ? LOW : HIGH));

}

//Reads the value from a specified digital pin, either HIGH or LOW.
byte PCF8574X3::digitalReadExpander(int pin)
{
	if (pin < 0 || pin > 23)
	{
		return;
	}

	setDevice(pin);
	if (expander == nullptr)
	{
		Serial.println("ERROR *ptr_expander in digitalReadExpander(int pin)");
		return;
	}

	if (_showLogDigitalReadExpander)
	{
		Serial.print("digitalReadExpander(");
		Serial.print(getPin(pin));
		Serial.println(")");
	}

	byte value = expander->digitalRead(getPin(pin));

	return value;
}

//Method sets the currently used expander for global pin
void PCF8574X3::setDevice(int pin)
{
	switch (pin)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		expander = &expander_x3_1;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		expander = &expander_x3_2;
		break;
	case 8:
	case 9:
	case 10:
	case 11:
		expander = &expander_x3_3;
		break;
	case 12:
	case 13:
	case 14:
	case 15:
		expander = &expander_x3_3;
		break;
	case 16:
	case 17:
	case 18:
	case 19:
		expander = &expander_x3_2;
		break;
	case 20:
	case 21:
	case 22:
	case 23:
		expander = &expander_x3_1;
		break;
	default:
		expander = nullptr;
	}
}

//Method returns the local pin of the device based on the global pin
int PCF8574X3::getPin(int pin)
{

	switch (pin)
	{
	case 0:
		return 7;
	case 1:
		return 6;
	case 2:
		return 5;
	case 3:
		return 4;
	case 4:
		return 7;
	case 5:
		return 6;
	case 6:
		return 5;
	case 7:
		return 4;
	case 8:
		return 7;
	case 9:
		return 6;
	case 10:
		return 5;
	case 11:
		return 4;
	case 12:
		return 3;
	case 13:
		return 2;
	case 14:
		return 1;
	case 15:
		return 0;
	case 16:
		return 3;
	case 17:
		return 2;
	case 18:
		return 1;
	case 19:
		return 0;
	case 20:
		return 3;
	case 21:
		return 2;
	case 22:
		return 1;
	case 23:
		return 0;
	default:
		return -1;
	}
}

