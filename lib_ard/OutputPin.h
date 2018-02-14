#ifndef LIB_ARD_OUTPUTPIN
#define LIB_ARD_OUTPUTPIN

#include "Pin.h"

namespace lib_ard
{
	class OutputPin : public Pin
	{
		private:
			PinType _tipoPin;	
		
		public:
			OutputPin (const unsigned short &number, PinType tipoPin);
			
			/*scrive sul pin hardware di arduino, 
				in un pin digitale il parametro val può assumere i valori LOW/HIGH
				in uno analogico può assumere un valore tra 0 e 255*/
			void write (unsigned short val) const;	
			
			/*restituisce il valore logico del pin:
			un pin digitale può restituire LOW/HIGH,
			un pin output analogico restituisce valori da 0 a 255*/ 
			unsigned short read () const;
			
			//restituisce il tipo di pin (DIGITAL/ANALOG)
			PinType getType() const;
			
			~OutputPin();
	};
}

#endif
