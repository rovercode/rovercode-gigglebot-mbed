#include "MicroBitEvent.h"

#include "inc/Gigglebot.h"
#include "inc/drivers/GigglebotLineSensors.h"

GigglebotLineSensors::GigglebotLineSensors(MicroBitI2C &_i2c) : i2c(_i2c), readings {0, 0},
    counter(GIGGLEBOT_START_COUNT_LINE_SENSORS)
{
}

uint16_t GigglebotLineSensors::getLeftReading()
{
    return this->readings[1];
}

uint16_t GigglebotLineSensors::getRightReading()
{
    return this->readings[0];
}

void GigglebotLineSensors::idleTick()
{
    char command = GET_LINE_SENSORS;
    char buffer[3];

    if (++counter < GIGGLEBOT_PERIOD_LINE_SENSORS)
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

    MicroBitEvent e(GIGGLEBOT_ID_LINE_SENSORS, GIGGLEBOT_LINE_SENSORS_EVT_UPDATE);
}