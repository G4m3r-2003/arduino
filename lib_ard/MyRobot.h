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

            long _spTot;    //lunghezza totale del tratto percorso
            long _spTotPrec;

            float _spX;     //componenti dello spostamento
            float _spY;
            
            float _angolo;
           
            signed short _potDesSx;
            signed short _potDesDx;

            long _controlTime;  //l'istante di tempo in cui è stato eseguito l'ultimo controllo

            bool _landing;  //indica se sto per arrivare a destinazione
        


            /*controlla il movimento del robot mantenendo su una traiettoria rettilinea.
              Restituisce l'istante di tempo in cui finisce il controllo, questo serve perchè è bene aspettare
              qualche centesimo di secondo prima di ripetere il controllo per evitare che esso sia instabile.
              ATTENZIONE QUESTA PARTE DOVREBBE NON SERVIRE PIU'

            long mantieniDirAvanti();
            long mantieniDirIndietro();
            */

            int findMax (int a, int b) const;
            int findMin(int a, int b) const;


            /*calcola e restituisce l'angolo a cui il robot 
              deve portarsi per tornare sulla corretta traiettoria rettilinea*/
            float calcAngTarget (long spTarget);


            /*queste due funzioni usano l'angolo target calcolato con la funzione sopra per annullare
              la componente y dello spostamento e rimanere quindi su una traiettoria rettilinea.
              La prima va usata per uno spostamento in avanti, la seconda indietro*/
            void mantieniTargetAvanti(long spTarget);
             
            void mantieniTargetIndietro(long spTarget);


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


            /*fa un campionamento degli encoder*/
            void campionaEnc();


            /*esegue uno spostamento rettilineo dello spazio indicato in cm*/
            bool spostaAlter(long spazioX);


            /*varie stampe*/
            void printEncoders() const;

            void printAngolo() const;

            void printServo() const;

            void printComponenti() const;

            /*azzera i passi degli encoder e le componenti dello spazio*/
            void reset();
    };
}


#endif