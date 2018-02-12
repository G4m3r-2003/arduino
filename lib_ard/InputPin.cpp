#include "InputPin.h"

namespace lib_ard
{
	InputPin::InputPin(const unsigned short &number, PinType tipoPin)
		: Pin(number), _tipoPin(tipoPin)
		{
			pinMode(getNumber(), INPUT);
		}
		
		unsigned short InputPin::read() const
		{
			return Pin::read(_tipoPin);
		}
		
		PinType InputPin::getType() const
		{
			return _tipoPin;
		}
}
