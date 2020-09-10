#include "MicroBitEvent.h"

#include "inc/Gigglebot.h"
#include "inc/drivers/GigglebotMotors.h"

GigglebotMotors::GigglebotMotors(MicroBitI2C &_i2c) : i2c(_i2c)
{
}

void GigglebotMotors::setMotorPower(char motor, int power, bool scaled)
{
    char buffer[3];

    buffer[0] = SET_MOTOR_POWER;
    buffer[1] = motor;
    buffer[2] = scaled ? SCALED_POWERS[power + 100] : power;

    this->i2c.write(I2C_ADDR, buffer, 3);
}
