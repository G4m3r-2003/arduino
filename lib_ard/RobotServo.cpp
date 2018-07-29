#include "RobotServo.h"

namespace lib_ard
{
	RobotServo::RobotServo(OutputPin &pinServo, ServoType tipoServo) : _pinServo(pinServo), _tipoServo(tipoServo)
	{		
	} 
	
	void RobotServo::setPotEff(signed short potEff)
	{
		_potEff=potEff;
	}
	
	
	void RobotServo::aziona()
	{
		if(_tipoServo==DIRETTO)
		{
			
			//Serial.println(_potEff);
			Servo::writeMicroseconds(1500+5*_potEff);
			
		}
		
		else 
		{
			//Serial.println(_potEff);
			Servo::writeMicroseconds(1500-5*_potEff);
		}
	}
	

	void RobotServo::inizializza()
	{
		attach(_pinServo.getNumber());
	}


	signed short RobotServo::getPotEff() const
	{
		return _potEff;
	}
}
