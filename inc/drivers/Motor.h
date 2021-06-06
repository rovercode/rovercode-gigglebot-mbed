#ifndef MOTOR_H
#define MOTOR_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

class Motor
{
    public:
    virtual ~Motor() {}

    /**
     * @param power ranges -100 to 100
     */
    virtual void setMotorPower(int power) = 0;
};
#endif
