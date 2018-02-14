#ifndef LIB_ARD_MYROBOT
#define LIB_ARD_MYROBOT



#include "Encoder.h"
#include "RobotServo.h"
#include "DigitalLed.h"

namespace lib_ard
{
    class MyRobot
    {
        private:
            RobotServo _servoSx;
            RobotServo _servoDx;

            Encoder _encSx;
            Encoder _encDx;

            DigitalLed _signalLed;

            long _spTot;
            float _angolo;
            
            signed short _potDesSx;
            signed short _potDesDx;


            /*controlla il movimento del robot mantenendo su una traiettoria rettilinea.
              Restituisce l'istante di tempo in cui finisce il controllo, questo serve perchè è bene aspettare
              qualche centesimo di secondo prima di ripetere il controllo per evitare che esso sia instabile*/
            int mantieniDirezione();


        public:
            MyRobot(RobotServo &servoSx, RobotServo &servoDx, Encoder &encSx, Encoder &encDx, DigitalLed &signalLed);

            void inizializza();
            
            /*restituisce l'angolo in radianti di cui è ruotato il robot a partire
              da un instante di riferimento, restituisce un numero positivo 
              se la rotazione è antioraria, negativo viceversa.
              Aggiorna l'attributo _angolo del robot*/
            float misuraAngolo();

            /*dà uno step per far ruotare il robottino fino all'angolo in radianti passato come parametro.
              Restituisce true se la rotazione è conclusa, false altrimenti.
              Questa funzione va chiamata nel loop finchè la rotazione non è conclusa*/
            bool ruota(float angTarget);

            /*fa avanzare il robot dello spazio selezionato*/
            void avanza(long spazio);

            /*fa un campionamento degli encoder*/
            void campionaEnc();


            /*fa spostare il robot dello spazio indicato come parametro.
              Spazio deve essere espresso in cm. Durante lo spostamento il robot mantiene la direzione
              iniziale fino alla fine dello spostamento.
              Restituisce l'istante dell'ultimo controllo sulla direzione*/
            int avanza(long spazio, int lastTime);


    };
}


#endif