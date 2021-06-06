#ifndef GIGGLEBOT_LIGHT_SENSORS_H
#define GIGGLEBOT_LIGHT_SENSORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

class GigglebotLightSensors : public MicroBitComponent
{
    MicroBitI2C i2c;
    uint16_t readings [2];
    uint16_t counter;

    public:
    GigglebotLightSensors(MicroBitI2C &_i2c);

    uint16_t getLeftReading();
    uint16_t getRightReading();

    /**
      * Periodic callback from MicroBit idle thread.
      */
    virtual void idleTick();
};
#endif
