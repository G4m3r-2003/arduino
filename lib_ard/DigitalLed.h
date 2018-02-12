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
			
			void turnOn() const;
			void turnOff() const;	
	};
}

#endif
