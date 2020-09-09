#include "MicroBitEvent.h"

#include "inc/Gigglebot.h"
#include "inc/drivers/GigglebotBattery.h"

GigglebotBattery::GigglebotBattery(MicroBitI2C &_i2c) : i2c(_i2c), voltage(0), counter(1000)
{
}

uint16_t GigglebotBattery::getVoltage()
{
    return this->voltage;
}

void GigglebotBattery::idleTick()
{
    char command = GET_VOLTAGE_BATTERY;
    char buffer[2];

    if (++counter < 1000)
    {
        return;
    }

    counter = 0;

    this->i2c.write(I2C_ADDR, &command, 1);
    this->i2c.read(I2C_ADDR, buffer, 2);
    this->voltage = buffer[0] << 8 | buffer[1];

    MicroBitEvent e(GIGGLEBOT_ID_BATTERY, GIGGLEBOT_BATTERY_EVT_UPDATE);
}
