#ifndef CUTEBOT_HEADLIGHT_H
#define CUTEBOT_HEADLIGHT_H

#include "MicroBitComponent.h"
#include "MicroBitI2C.h"

enum CutebotHeadlightId {
    CUTEBOT_HEADLIGHT_ID_LEFT = 4,
    CUTEBOT_HEADLIGHT_ID_RIGHT = 8,
};

class CutebotHeadlight
{
    MicroBitI2C &i2c;
    CutebotHeadlightId headlightId;

    public:
    CutebotHeadlight(MicroBitI2C &_i2c, CutebotHeadlightId _headlightId);
    int setHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
};
#endif
