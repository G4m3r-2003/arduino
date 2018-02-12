#ifndef LIB_ARD_ENC_H
#define LIB_ARD_ENC_H

#include "InputPin.h"

namespace lib_ard
{
	class Encoder
	{
		private:
			InputPin _pinA;						//i due pin a cui è collegato l'encoder
			InputPin _pinB;
			
			unsigned short _valAvanti[4];					//i valori attesi se l'encoder gira in avanti
			unsigned short _valIndietro[4]; 			//valori attesi se si gira indietro
			unsigned short _lastStep; 						//il valore dell'encoder quando è stato eseguito l'ultimo passo
			long int _spPerc;
			
			unsigned short read() const; 					//converte i due valori digitali letti dai due pin in un unico valore decimale
		
		public:
			Encoder(InputPin &pinA, InputPin &pinB);
			
			/*restituisce la direzione in cui si sta muovendo l'encoder e
			 incrementa lo spazio percorso dall'encoder*/
			signed short countDirection();	
									
			long int getSpace() const;
	};
}

#endif
