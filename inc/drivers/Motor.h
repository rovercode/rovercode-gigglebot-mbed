#ifndef MOTOR_H
#define MOTOR_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

class Motor
{
    public:

    /**
     * @param power ranges -100 to 100
     * @param scale adjust the power value to avoid the lowest power settings
     */
    virtual void setMotorPower(int power) = 0;
};
#endif
