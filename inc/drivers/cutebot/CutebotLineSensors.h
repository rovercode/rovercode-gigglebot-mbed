#ifndef CUTEBOT_LINE_SENSORS_H
#define CUTEBOT_LINE_SENSORS_H

#include "MicroBitComponent.h"
#include "MicroBitIO.h"

class CutebotLineSensors : public MicroBitComponent
{
    MicroBitIO &io;
    uint16_t readings [2];
    uint16_t counter;

    public:
    CutebotLineSensors(MicroBitIO &_io);

    uint16_t getLeftReading();
    uint16_t getRightReading();

    /**
      * Periodic callback from MicroBit idle thread.
      */
    virtual void idleTick();
};
#endif
