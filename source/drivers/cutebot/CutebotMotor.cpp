#include "MicroBitEvent.h"

#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

/* Reference: https://github.com/elecfreaks/pxt-cutebot */

CutebotMotor::CutebotMotor(MicroBitI2C &_i2c, CutebotMotorId _motorId) : i2c(_i2c), motorId(_motorId)
{
}

void CutebotMotor::setMotorPower(int power)
{
    char buffer[4];

    buffer[0] = this->motorId;
    buffer[1] = power > 0 ? 0x02 : 0x01;
    buffer[2] = power > 0 ? power : power * -1;
    buffer[3] = 0;

    this->i2c.write(CUTEBOT_I2C_ADDR, buffer, 4);
}
