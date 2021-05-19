#ifndef CUTEBOT_DISTANCE_SENSOR_H
#define CUTEBOT_DISTANCE_SENSOR_H

#include "MicroBitComponent.h"
#include "MicroBitIO.h"

class CutebotDistanceSensor : public MicroBitComponent
{
    MicroBitIO &io;
    uint16_t distance;
    uint16_t counter;

    public:
    CutebotDistanceSensor(MicroBitIO &_io);

    uint16_t getDistance();

    /**
      * Periodic callback from MicroBit idle thread.
      */
    virtual void idleTick();
};
#endif
