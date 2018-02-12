#include "DigitalLed.h"

namespace lib_ard
{
	DigitalLed::DigitalLed(OutputPin &pinLed) : _pinLed(pinLed)
	{
	}
	
	void DigitalLed::turnOn() const
	{
		if(_pinLed.getType()==DIGITAL)
			_pinLed.write(HIGH);
		
		else
			_pinLed.write(250);	
	}
	
	void DigitalLed::turnOff() const
	{
		if(_pinLed.getType()==DIGITAL)
		_pinLed.write(LOW);
		
		else
			_pinLed.write(0);	
	}
}
