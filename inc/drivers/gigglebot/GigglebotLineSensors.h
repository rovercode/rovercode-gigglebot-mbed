#ifndef GIGGLEBOT_LINE_SENSORS_H
#define GIGGLEBOT_LINE_SENSORS_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

class GigglebotLineSensors : public MicroBitComponent
{
    MicroBitI2C &i2c;
    uint16_t readings [2];
    uint16_t counter;

    public:
    GigglebotLineSensors(MicroBitI2C &_i2c);

    uint16_t getLeftReading();
    uint16_t getRightReading();

    /**
      * Periodic callback from MicroBit idle thread.
      */
    virtual void idleTick();
};
#endif
