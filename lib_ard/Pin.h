#ifndef LIB_ARD_PIN
#define LIB_ARD_PIN

#include "Arduino.h"
#include "PinType.h"

//in generale è buona regola aggiungere le #ifndef negli header 
//per evitare inclusioni ricorsive o multiple
namespace lib_ard
{
  class Pin
  {
    private:
        unsigned short   _number;
		
		protected:
		  unsigned short int read (PinType tipoPin) const;
		
    public:
		//ho aggiunto explicit per evitare la conversione implicita tra short e Pin
	
    	Pin(const unsigned short &number);		//explicit potrebbe funzionare diversamente se non si usa c++11
     
			unsigned short int getNumber() const;
  };
}

#endif //LIB_ARD_PIN_H
