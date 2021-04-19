#ifndef GIGGLEBOT_BATTERY_H
#define GIGGLEBOT_BATTERY_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

class GigglebotBattery : public MicroBitComponent
{
    MicroBitI2C i2c;
    uint16_t voltage;
    uint16_t counter;

    public:
    GigglebotBattery(MicroBitI2C &_i2c);

    uint16_t getVoltage();

    /**
      * Periodic callback from MicroBit idle thread.
      */
    virtual void idleTick();
};
#endif
