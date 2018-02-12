#include "Encoder.h"

namespace lib_ard
{
	Encoder::Encoder(InputPin &pinA, InputPin &pinB) : _pinA(pinA), _pinB(pinB)
	{
		_valAvanti[0] = 1;
		_valAvanti[1] = 3;
		_valAvanti[2] = 0;
		_valAvanti[3] = 2;
		
		_valIndietro[0] = 2;
		_valIndietro[1] = 0;
		_valIndietro[2] = 3;
		_valIndietro[3] = 1;
		
		_spPerc=0;
		
		
		_lastStep=Encoder::read();
	}
	
	unsigned short Encoder::read() const
	{
		int stateA=(_pinA.read())<<1, stateB=_pinB.read();
		
		//Serial.println(stateA+stateB);
		
		return stateA + stateB;
	}
	
	signed short Encoder::countDirection()
	{
		int valCor = Encoder::read();
		
		if (valCor == _valAvanti[_lastStep])		//confronta il valore corrente con l'ordine stabilito nell'array
		{
			_lastStep=valCor;
			_spPerc++;
			return 1;
		}
			
		else if (valCor == _valIndietro[_lastStep])
		{
			_lastStep=valCor;
			_spPerc--;
			return -1;
		}	
		
		else return 0;
	}
	
	
	long int Encoder::getSpace() const
	{
		return _spPerc;
	}
}
