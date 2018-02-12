#include "OutputPin.h"

namespace lib_ard
{
	OutputPin::OutputPin(const unsigned short  &number, PinType tipoPin) 
		: Pin(number), _tipoPin (tipoPin)		//come si chiama la classe base?
	{
		pinMode(getNumber(), OUTPUT);
	}
	
	void OutputPin::write (unsigned short val ) const	//Perchè non vede _number e _tipoPin
	{
		if (_tipoPin == ANALOG)
			analogWrite(getNumber(), val);
			
		else digitalWrite (getNumber(), val);	
	}
	
	OutputPin::~OutputPin()
	{
		write(LOW);
	}
	
	unsigned short OutputPin::read() const
	{
		return Pin::read(_tipoPin);
	}
	
		PinType OutputPin::getType() const
		{
			return _tipoPin;
		}
	
}
