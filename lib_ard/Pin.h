#ifndef LIB_ARD_PIN
#define LIB_ARD_PIN

#include "Arduino.h"
#include "PinType.h"


namespace lib_ard
{
  class Pin
  {
    private:
        unsigned short   _number;
		
		protected:
			
			/*funzione di appoggio usata da input e output
			 pins per chiamare le read di basso livello*/
		  unsigned short int read (PinType tipoPin) const;
		
    public:
	
    	Pin(const unsigned short &number);	
     
			/*restituisce il numero del pin hardware di arduino*/     
			unsigned short int getNumber() const;
  };
}

#endif
