#ifndef GIGGLEBOT_BATTERY_H
#define GIGGLEBOT_BATTERY_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

#define GIGGLEBOT_BATTERY_EVT_UPDATE         1

class GigglebotBattery : public MicroBitComponent
{
    MicroBitI2C i2c;
    uint16_t voltage;

    public:
    GigglebotBattery(MicroBitI2C &_i2c);

    uint16_t getVoltage();

    /**
      * Periodic callback from MicroBit idle thread.
      */
    virtual void idleTick();
};
#endif
