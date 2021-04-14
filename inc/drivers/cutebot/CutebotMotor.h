#ifndef GIGGLEBOT_MOTORS_H
#define GIGGLEBOT_MOTORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"
#include "inc/drivers/Motor.h"

enum CutebotMotorId {
  MOTOR_ID_RIGHT = 1,
  MOTOR_ID_LEFT,
  MOTOR_ID_BOTH
};

class CutebotMotor : public Motor
{
    MicroBitI2C i2c;
    CutebotMotorId motorId;

    private:
    void setSingleMotorPower(int motorId, int power);

    public:
    CutebotMotor(MicroBitI2C &_i2c, CutebotMotorId _motorId);

    /**
     * @param power ranges -100 to 100
     */
    void setMotorPower(int power);
};
#endif
