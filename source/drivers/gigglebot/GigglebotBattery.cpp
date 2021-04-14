#include "MicroBitEvent.h"

#include "inc/Gigglebot.h"
#include "inc/drivers/gigglebot/GigglebotBattery.h"

GigglebotBattery::GigglebotBattery(MicroBitI2C &_i2c) : i2c(_i2c), voltage(0),
    counter(GIGGLEBOT_PERIOD_BATTERY - GIGGLEBOT_START_COUNT_BATTERY)
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

    if (++counter < GIGGLEBOT_PERIOD_BATTERY)
    {
        return;
    }

    counter = 0;

    this->i2c.write(I2C_ADDR, &command, 1);
    this->i2c.read(I2C_ADDR, buffer, 2);
    this->voltage = buffer[0] << 8 | buffer[1];

    MicroBitEvent e(GIGGLEBOT_ID_BATTERY, GIGGLEBOT_BATTERY_EVT_UPDATE);
}
