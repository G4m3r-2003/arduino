#ifndef LIB_ARD_DIG_LED
#define LIB_ARD_DIG_LED

#include "OutputPin.h"

namespace lib_ard
{
	class DigitalLed
	{
		private:
			OutputPin _pinLed;
		
		public:
			DigitalLed(OutputPin &pinLed);
			
			/*accende il led, è adattata in modo da funzionare anche se il led è stato collegato
				ad un pin analogico*/
			void turnOn() const;
			
			/*spegne il led, funziona sia con pin analogici che digitali*/
			void turnOff() const;	
	};
}

#endif
