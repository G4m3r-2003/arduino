#ifndef LIB_ARD_ROBOT_BUILDER
#define LIB_ARD_ROBOT_BUILDER

#include "MyRobot.h"

namespace lib_ard
{
    OutputPin pinServoSx(9, ANALOG);
    OutputPin pinServoDx(10, ANALOG);

    InputPin pinEncSx1(6, DIGITAL);
    InputPin pinEncSx2(7, DIGITAL);

    InputPin pinEncDx1(4, DIGITAL);
    InputPin pinEncDx2(5, DIGITAL);

    OutputPin pinLed(3, DIGITAL);

    RobotServo servoSx(pinServoSx, DIRETTO);
    RobotServo servoDx(pinServoDx, INVERSO);

    Encoder encSx(pinEncSx1, pinEncSx2);
    Encoder encDx(pinEncDx1, pinEncDx2);

    DigitalLed led(pinLed);

    MyRobot rob(servoSx, servoDx, encSx, encDx, led);
}



#endif