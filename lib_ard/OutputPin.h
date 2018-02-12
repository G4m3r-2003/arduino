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
			
			void write (unsigned short val) const;	//write chiama digital o analog in base al tipo del pin
			
			unsigned short read () const;
			
			PinType getType() const;
			
			~OutputPin();
	};
}

#endif
