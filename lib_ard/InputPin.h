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
			
			/**
			* 
			* @param
			* @return 
			*/
			unsigned short read () const;	
			
			PinType getType() const;
	};
}

#endif
