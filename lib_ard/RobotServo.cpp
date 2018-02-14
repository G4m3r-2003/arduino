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
			
			Servo::writeMicroseconds(1500+5*_potEff);
			
		}
		
		else 
		{
			Servo::writeMicroseconds(1500-5*_potEff);
		}
	}
	

	void RobotServo::inizializza()
	{
		attach(_pinServo.getNumber());
	}


	int RobotServo::getPotEff()
	{
		return _potEff;
	}
}
