#ifndef GIGGLEBOT_MOTORS_H
#define GIGGLEBOT_MOTORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

enum GigglebotMotorId {
  MOTOR_ID_RIGHT = 1,
  MOTOR_ID_LEFT,
  MOTOR_ID_BOTH
};

class GigglebotMotor
{
    MicroBitI2C i2c;
    const static short int SCALED_POWERS[];
    GigglebotMotorId motorId;

    public:
    GigglebotMotor(MicroBitI2C &_i2c, GigglebotMotorId _motorId);

    /**
     * @param power ranges -100 to 100
     * @param scale adjust the power value to avoid the lowest power settings
     */
    void setMotorPower(int power, bool scale = false);


};
#endif
