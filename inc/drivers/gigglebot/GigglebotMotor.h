#ifndef GIGGLEBOT_MOTORS_H
#define GIGGLEBOT_MOTORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"
#include "inc/drivers/Motor.h"

enum GigglebotMotorId {
  GIGGLEBOT_MOTOR_ID_RIGHT = 1,
  GIGGLEBOT_MOTOR_ID_LEFT,
  GIGGLEBOT_MOTOR_ID_BOTH
};

class GigglebotMotor : public Motor
{
    MicroBitI2C &i2c;
    const static short int SCALED_POWERS[];
    GigglebotMotorId motorId;

    public:
    GigglebotMotor(MicroBitI2C &_i2c, GigglebotMotorId _motorId);

    /**
     * @param power ranges -100 to 100
     */
    void setMotorPower(int power);
};
#endif
