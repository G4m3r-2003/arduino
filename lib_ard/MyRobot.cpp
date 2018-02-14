#include "MyRobot.h"

#define DIST  84.0338       //la misura dell'asse espressa in unità encoder
#define TOLL_ANG 0.2       //la tolleranza sull'angolo misurata in radianti (circa 3 gradi)
#define TOLL_DIST  3    //la tolleranza sulla distanza percorsa
#define MAXDIST 30    //la distanza dallo spazio finale da percorrere entro la quale viene limitata la potenza dei servo
#define MAXANG 0.4      //la distanza dall'angolo finale da percorrere entro la quale viene limitata la potenza dei servo
#define MINPOW 35
#define DIAMETRO 6.4
#define MINTIME 20     //il tempo minimo di attesa tra due controlli consecutivi

namespace lib_ard
{
    MyRobot::MyRobot(RobotServo &servoSx, RobotServo &servoDx, Encoder &encSx, Encoder &encDx, DigitalLed &signalLed)
        : _servoSx(servoSx), _servoDx(servoDx), _encSx(encSx), _encDx(encDx), _signalLed(signalLed)
    {
    }    

    void MyRobot::inizializza()
    {
        _servoSx.inizializza();
        _servoDx.inizializza();
    }

    float MyRobot::misuraAngolo()
    {
        _angolo = (_encDx.getSteps()-_encSx.getSteps())/DIST;
        
        //Serial.println(_encSx.getSteps());

        return _angolo;
    }

    bool MyRobot::ruota(float angTarget)
    {
        MyRobot::misuraAngolo();
        
        bool finito=false;

        Serial.println(_angolo);

        if(_angolo > angTarget + MAXANG)
        {   
            _servoSx.setPotEff(100);
            _servoDx.setPotEff(-100);
        }

        else if(_angolo > angTarget + TOLL_ANG)
        {
            _servoSx.setPotEff(MINPOW);
            _servoDx.setPotEff(-MINPOW);
        }

        else if(_angolo < angTarget - MAXANG)
        {
            _servoSx.setPotEff(-100);
            _servoDx.setPotEff(100);
        }

        else if(_angolo < angTarget - TOLL_ANG)
        {
            _servoSx.setPotEff(-MINPOW);
            _servoDx.setPotEff(MINPOW);
        }

        else 
        {   
            _servoSx.setPotEff(0);
            _servoDx.setPotEff(0);
            finito=true; 
        }

        _servoSx.aziona();
        _servoDx.aziona();

        return finito;
    }


    void MyRobot::campionaEnc()
    {
        _encSx.countDirection();
        _encDx.countDirection();
    }


    int MyRobot::mantieniDirezione()
    {
        misuraAngolo();

        if(_angolo>TOLL_ANG)
        {
            _servoSx.setPotEff(_potDesSx);
            _servoDx.setPotEff(_servoDx.getPotEff()-1);
        }

        else if(_angolo<-TOLL_ANG)
        {   
            _servoDx.setPotEff(_potDesDx);
            _servoSx.setPotEff(_servoSx.getPotEff()-1);
        }

        else
        {
            _servoSx.setPotEff(_potDesSx);
            _servoDx.setPotEff(_potDesDx);
        }

        return millis();
    } 


    int MyRobot::avanza (long spazio, int lastTime)
    {
        long spDaFare = spazio/(PI*DIAMETRO)*120;
        
        
        /*...trovare spazio già percorso, decidere velocità, decidere se fare il controllo, 
          azionare i servo e restituire l'istante dell'ultimo controllo*/
        
        _spTot= (_encSx.getSteps()+_encDx.getSteps())/2;       //lo spazio percorso è la media di quello misurato dai due encoder
       
       if (_spTot < spDaFare - MAXDIST)
       {
           _potDesSx=100;
           _potDesDx=100;
       }

       else if (_spTot < spDaFare - TOLL_DIST)
       {
           _potDesSx=MINPOW;
           _potDesDx=MINPOW;
       }

       else if (_spTot > spDaFare + MAXDIST)
       {
            _potDesSx=-100;
            _potDesDx=-100;
       }

       else if (_spTot >spDaFare + TOLL_DIST)
       {
            _potDesSx=-MINPOW;
            _potDesDx=-MINPOW; 
       }

       else 
       {
           _potDesSx=0;
           _potDesDx=0;
       }
       
       int t1;

       t1= millis();

       if (t1-lastTime > MINTIME)
       {
           lastTime = mantieniDirezione();
       }

       _servoSx.aziona();
       _servoDx.aziona();

       return lastTime;
    }
}