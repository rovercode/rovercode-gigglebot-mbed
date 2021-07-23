#ifndef CUTEBOT_MOTORS_H
#define CUTEBOT_MOTORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"
#include "inc/drivers/Motor.h"

enum CutebotMotorId {
  CUTEBOT_MOTOR_ID_LEFT = 1,
  CUTEBOT_MOTOR_ID_RIGHT,
};

class CutebotMotor : public Motor
{
    MicroBitI2C &i2c;
    CutebotMotorId motorId;

    private:
    void setSingleMotorPower(CutebotMotorId motorId, int power);

    public:
    CutebotMotor(MicroBitI2C &_i2c, CutebotMotorId _motorId);

    /**
     * @param power ranges -100 to 100
     */
    void setMotorPower(int power);
};
#endif
