#ifndef LIB_ARD_ROBOT_SERVO
#define LIB_ARD_ROBOT_SERVO

#include "Servo.h"
#include "OutputPin.h"

namespace lib_ard
{
	enum ServoType
	{
		DIRETTO=1,
		INVERSO=-1
	};
	
	//i servo devono essere costruiti nel setup
	
	
	class RobotServo : public Servo
	{
		private :
			signed short _potEff;			//numeri da -100 a 100 che esprimono la potenza
			signed short _potDes;			//in percentuale rispetto alla massima		
								
			ServoType _tipoServo;
			OutputPin _pinServo;
			
		public : 	
			RobotServo(OutputPin &pinServo, ServoType tipoServo);
			
			void setPotEff(signed short potEff);
			void setPotDes(signed short potDes);
			void aziona ();			//accende il servo, la potenza applicata dal servo è quella effettiva
			void inizializza(); // fa l'attach() del servo al pin
	};
}




#endif
