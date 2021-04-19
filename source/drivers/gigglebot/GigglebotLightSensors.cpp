#include "MicroBitEvent.h"

#include "inc/drivers/gigglebot/Gigglebot.h"
#include "inc/drivers/gigglebot/GigglebotLightSensors.h"

GigglebotLightSensors::GigglebotLightSensors(MicroBitI2C &_i2c) : i2c(_i2c), readings {0, 0},
    counter(GIGGLEBOT_PERIOD_LIGHT_SENSORS - GIGGLEBOT_START_COUNT_LIGHT_SENSORS)
{
}

uint16_t GigglebotLightSensors::getLeftReading()
{
    return this->readings[1];
}

uint16_t GigglebotLightSensors::getRightReading()
{
    return this->readings[0];
}

void GigglebotLightSensors::idleTick()
{
    char command = GET_LIGHT_SENSORS;
    char buffer[3];

    if (++counter < GIGGLEBOT_PERIOD_LIGHT_SENSORS)
    {
        return;
    }

    counter = 0;

    this->i2c.write(GIGGLEBOT_I2C_ADDR, &command, 1);
    this->i2c.read(GIGGLEBOT_I2C_ADDR, buffer, 3);
    for (int i=0; i<2; i++) {
        this->readings[i] = buffer[i] << 2;
        this->readings[i] |= ((buffer[2] << (i * 2)) & 0xC0) >> 6;
        this->readings[i] = 1023 - this->readings[i];
    }

    MicroBitEvent e(BOT_ID_LIGHT_SENSORS, BOT_LIGHT_SENSORS_EVT_UPDATE);
}
