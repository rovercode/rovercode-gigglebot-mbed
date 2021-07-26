#include "MicroBitEvent.h"

#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotLineSensors.h"

CutebotLineSensors::CutebotLineSensors(MicroBitIO &_io) : io(_io), readings {0, 0},
    counter(CUTEBOT_PERIOD_LINE_SENSORS - CUTEBOT_START_COUNT_LINE_SENSORS)
{
    io.P13.setPull(PullNone);
    io.P14.setPull(PullNone);
}

uint16_t CutebotLineSensors::getLeftReading()
{
    return this->readings[0];
}

uint16_t CutebotLineSensors::getRightReading()
{
    return this->readings[1];
}

void CutebotLineSensors::idleTick()
{
    if (++counter < CUTEBOT_PERIOD_LINE_SENSORS)
    {
        return;
    }

    counter = 0;

    this->readings[0] = io.P13.getDigitalValue() * 1023;
    this->readings[1] = io.P14.getDigitalValue() * 1023;
    MicroBitEvent e(BOT_ID_LINE_SENSORS, BOT_LINE_SENSORS_EVT_UPDATE);
}
