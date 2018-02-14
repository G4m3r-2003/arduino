#ifndef LIB_ARD_INPUT
#define LIB_ARD_INPUT

#include "Pin.h"

namespace lib_ard
{
	class InputPin : public Pin
	{
		private :
			PinType _tipoPin;
			
		public :
			InputPin (const unsigned short &number, PinType tipoPin);
			
			/*restituisce il valore logico del pin:
				un pin digitale può restituire LOW/HIGH,
				un pin input analogico restituisce valori da 0 a 1023*/
			unsigned short read () const;	
			
			//restituisce il tipo di pin (DIGITAL/ANALOG)
			PinType getType() const;
	};
}

#endif
