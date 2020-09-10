#ifndef GIGGLEBOT_MOTORS_H
#define GIGGLEBOT_MOTORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

#define GIGGLEBOT_MOTORS_EVT_UPDATE         1

class GigglebotMotors
{
    MicroBitI2C i2c;

    public:
    GigglebotMotors(MicroBitI2C &_i2c);

    /**
     * @param motor 0x01 left, 0x02 right, 0x03 both
     * @param power ranges -100 to 100
     */
    void setMotorPower(char motor, int power);
};
#endif
