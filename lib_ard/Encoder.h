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
			
			unsigned short _valAvanti[4];				//i valori attesi se l'encoder gira in avanti
			unsigned short _valIndietro[4]; 		//valori attesi se si gira indietro
			unsigned short _lastStep; 			//il valore dell'encoder quando è stato eseguito l'ultimo passo
			long int _numPassi;				//i passi effettuati dall'encoder a partire da un istante di riferimento 
			
			
			/*legge i due pin a cui è collegato l'encoder e converte
				i due valori binari in un unico decimale da 0 a 3*/
			unsigned short read() const; 
		
		public:
			Encoder(InputPin &pinA, InputPin &pinB);
			
			/*incrementa o decrementa il numero di passi effettuati dall'encoder, 
				restituisce 1 se l'encoder sta girando in senso antiorario, 
				0 se fermo, -1 se in senso orario*/
			signed short countDirection();	
			
			/*restituisce il numero di passi effettuati dall'encoder*/						
			long int getSteps() const;
			
			/*resetta a 0 il numero di passi*/
			void resetSteps();
	};
}

#endif
