#include "MicroBitEvent.h"

#include "inc/Cutebot.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

/* Reference: https://github.com/elecfreaks/pxt-cutebot */

void CutebotMotor::setSingleMotorPower(int motorId, int power) {
    char buffer[4];

    buffer[0] = motorId;
    buffer[0] = power > 0 ? 0x02 : 0x01;
    buffer[2] = power > 0 ? power : power * -1;
    buffer[3] = 0;

    this->i2c.write(I2C_ADDR, buffer, 4);
}

CutebotMotor::CutebotMotor(MicroBitI2C &_i2c, CutebotMotorId _motorId) : i2c(_i2c), motorId(_motorId)
{
}

void CutebotMotor::setMotorPower(int power)
{
    if (this->motorId == MOTOR_ID_BOTH) {
        this->setSingleMotorPower(MOTOR_ID_LEFT, power);
        this->setSingleMotorPower(MOTOR_ID_RIGHT, power);
    } else {
        this->setSingleMotorPower(this->motorId, power);
    }
}
