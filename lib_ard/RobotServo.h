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
	
	//IMPORTANTE: i servo devono essere costruiti nel setup
	
	
	class RobotServo : public Servo
	{
		private :
			signed short _potEff;			//numer0 da -100 a 100 che esprime la potenza applicata al servo 
																//in percentuale rispetto alla massima		
								
			ServoType _tipoServo;		//può essere DIRETTO o INVERSO in base alla polarità
			OutputPin _pinServo;
			
		public : 	
			RobotServo(OutputPin &pinServo, ServoType tipoServo);
			
			/*imposta la potenza che che effettivamente è data al servo 
				nel momento in cui è azionato*/
			void setPotEff(signed short potEff);

			signed short getPotEff() const;
			
			/*muove il servo dando la potenza impostata in _potEff*/
			void aziona ();		
			
			/*inizializza il servo facendo l'attach e aprendo un canale con il pin output.
				Questa funzione va eseguita nel setup per funzionare correttamente*/
			void inizializza(); 
	};
}




#endif
