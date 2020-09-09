#include "MicroBitEvent.h"

#include "inc/Gigglebot.h"
#include "inc/drivers/GigglebotLightSensors.h"

GigglebotLightSensors::GigglebotLightSensors(MicroBitI2C &_i2c) : i2c(_i2c), readings {0, 0},
    counter(GIGGLEBOT_START_COUNT_LIGHT_SENSORS)
{
}

uint16_t GigglebotLightSensors::getLeftReading()
{
    return this->readings[0];
}

uint16_t GigglebotLightSensors::getRightReading()
{
    return this->readings[1];
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

    this->i2c.write(I2C_ADDR, &command, 1);
    this->i2c.read(I2C_ADDR, buffer, 3);
    for (int i=0; i<2; i++) {
        this->readings[i] = buffer[i] << 2;
        this->readings[i] |= ((buffer[2] << (i * 2)) & 0xC0) >> 6;
        this->readings[i] = 1023 - this->readings[i];
    }

    MicroBitEvent e(GIGGLEBOT_ID_LIGHT_SENSORS, GIGGLEBOT_LIGHT_SENSORS_EVT_UPDATE);
}
