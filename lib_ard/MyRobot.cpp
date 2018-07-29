#include "MyRobot.h"
#include "math.h"

#define STEPPERROT 240      //numero di step encoder per un giro della ruota
#define DIST  172.252       //la misura dell'asse espressa in unità encoder
#define TOLL_ANG 0.015       //la tolleranza sull'angolo misurata in radianti ()
#define TOLL_DIST  3    //la tolleranza sulla distanza percorsa
#define MAXDIST 15    //la distanza dallo spazio finale da percorrere entro la quale viene limitata la potenza dei servo
#define MAXANG 0.7      //la distanza dall'angolo finale da percorrere entro la quale viene limitata la potenza dei servo
#define MINPOW 40
#define DIAMETRO 6.84
#define MINTIME 20     //il tempo minimo di attesa tra due controlli consecutivi
#define SERVO_OFFSET 20  //alla velocità max avanti il servo destro raggiunge
                        // quello sinistro con una potenza impostata +15
                        //vice versa con vMax indietro

namespace lib_ard
{
    MyRobot::MyRobot(RobotServo &servoSx, RobotServo &servoDx, Encoder &encSx, Encoder &encDx, DigitalLed &signalLed)
        : _servoSx(servoSx), _servoDx(servoDx), _encSx(encSx), _encDx(encDx), _signalLed(signalLed)
    {
        _spTotPrec=0;
        _spX=0;
        _spY=0;
    }    


    void MyRobot::inizializza()
    {
        _servoSx.inizializza();
        _servoDx.inizializza();
    }


    float MyRobot::misuraAngolo()
    {

        _angolo = fmod((_encDx.getSteps()-_encSx.getSteps())/DIST, 2*PI) ;
        
        //Serial.println(_angolo);

        return _angolo;
    }


    bool MyRobot::ruota(float angTarget)
    {
        MyRobot::misuraAngolo();
        
        bool finito=false;

        if(_angolo > angTarget + MAXANG)
        {   
            _servoSx.setPotEff(100);
            _servoDx.setPotEff(-100);
        }

        else if(_angolo < angTarget - MAXANG)
        {   
            _servoSx.setPotEff(-100);
            _servoDx.setPotEff(100);
        }

        else if(_angolo > angTarget + TOLL_ANG)
        {
            _servoSx.setPotEff(MINPOW);
            _servoDx.setPotEff(-MINPOW);
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


    bool MyRobot::spostaAlter(long spazioX)
    {   
        spazioX= spazioX/(PI*DIAMETRO)*STEPPERROT;
        
        _landing=false;
        
        long spTotCor = (_encSx.getSteps()+_encDx.getSteps())/2;
        misuraAngolo();

        long deltaS=spTotCor-_spTotPrec;
      
        _spX+=deltaS*cos(_angolo);
        _spY+=deltaS*sin(_angolo);

        _spTotPrec=spTotCor;

        bool avanti;

        if (_spX < spazioX - MAXDIST)
        {
           _potDesSx=100;
           _potDesDx=100 + SERVO_OFFSET;
           avanti=true;
        }

       else if (_spX < spazioX - TOLL_DIST)
       {
           _potDesSx=MINPOW;
           _potDesDx=MINPOW;
           _landing=true;
       }

       else if (_spX > spazioX + MAXDIST)
       {
            _potDesSx=-100 - SERVO_OFFSET;
            _potDesDx=-100;
            avanti=false;
       }

       else if (_spX >spazioX + TOLL_DIST)
       {
            _potDesSx=-MINPOW;
            _potDesDx=-MINPOW; 
            _landing=true;
       }

       else 
       {
           _potDesSx=0;
           _potDesDx=0;

           _landing=true;
       }
       
       if(avanti)
        mantieniTargetAvanti(spazioX);
       else mantieniTargetIndietro(spazioX); 
    
       bool finito=false;

       if(_servoDx.getPotEff()==0 && _servoSx.getPotEff()==0)
       {
           finito = true;
       }

       _servoSx.aziona();
       _servoDx.aziona();

       return finito;
    }


    void MyRobot::printEncoders() const
    {
        Serial.print("Encoder Sx: ");
        Serial.print(_encSx.getSteps());
        Serial.print("|| Encoder Dx: "); 
        Serial.println(_encDx.getSteps());
    }


    int MyRobot::findMax(int a, int b) const
    {
        if(a > b)
            return a;
        else return b;    
    }


    void MyRobot::printAngolo() const
    {
        Serial.print("Angolo = ");
        Serial.println(_angolo);
    }

    
    void MyRobot::printServo() const
    {
        Serial.print("ServoSx: ");
        Serial.print(_servoSx.getPotEff());
        Serial.print(" || ServoDx: ");
        Serial.println(_servoDx.getPotEff());
    }


    int MyRobot::findMin(int a, int b) const
    {
        if(a < b)
            return a;
        else return b;    
    }


    void MyRobot::reset()
    {
        _encSx.resetSteps();
        _encDx.resetSteps();

        _spX=0;
        _spY=0;
        _spTotPrec=0;
    }


    void MyRobot::printComponenti() const
    {
        Serial.print("X = ");
        Serial.print(_spX);
        Serial.print(" | Y = ");
        Serial.print(_spY);
    }


    float MyRobot::calcAngTarget(long spTarget)
    {
        float tg=_spY/((float)spTarget-_spX);

        return -atan(tg);
    }


    void MyRobot::mantieniTargetAvanti(long spTarget)
    {
            float angolo = calcAngTarget(spTarget);

            Serial.print("|Rientro=");
            Serial.print(angolo);

            if(_angolo > angolo && !_landing)
            {
                _servoSx.setPotEff(_potDesSx);
                _servoDx.setPotEff(findMin(_potDesDx,findMax(0, _servoDx.getPotEff()-2)));
            }

            else if(_angolo < angolo && !_landing)
            {   
                _servoDx.setPotEff(_potDesDx);
                _servoSx.setPotEff(findMin(_potDesSx, findMax(0, _servoSx.getPotEff()-2)));
            }

            else
            {
                _servoSx.setPotEff(_potDesSx);
                _servoDx.setPotEff(_potDesDx);
            } 

    }


    void MyRobot::mantieniTargetIndietro(long spTarget)
    {
        float angolo = calcAngTarget(spTarget);

        Serial.print("|Rientro=");
        Serial.print(angolo);

        if(_angolo > angolo && !_landing)
        {
            _servoDx.setPotEff(_potDesDx);
            _servoSx.setPotEff(findMax(_potDesSx, findMin(0, _servoSx.getPotEff()+3)));
        }

        else if(_angolo < angolo && !_landing)
        {   
            _servoSx.setPotEff(_potDesSx);
            _servoDx.setPotEff(findMax(_potDesDx,findMin(0, _servoDx.getPotEff()+3)));
        }

        else
        {
            _servoSx.setPotEff(_potDesSx);
            _servoDx.setPotEff(_potDesDx);
        }
    }
}