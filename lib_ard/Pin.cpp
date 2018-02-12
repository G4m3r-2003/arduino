#include "Pin.h"

namespace lib_ard
{
	//definire tutte le costanti con i nomi dei pin
	
    Pin::Pin(const unsigned short &number) : _number(number)
    {}

    unsigned short int Pin::getNumber() const
    {
        return _number;
    }

    unsigned short int Pin::read(PinType tipoPin) const
    {
    	if(tipoPin == ANALOG)
        return analogRead(_number);
      else return digitalRead(_number);  
    }

}
