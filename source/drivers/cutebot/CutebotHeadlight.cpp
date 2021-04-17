#include "MicroBit.h"
#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotHeadlight.h"

CutebotHeadlight::CutebotHeadlight(MicroBitI2C &_i2c, CutebotHeadlightId _headlightId) :
    i2c(_i2c), headlightId(_headlightId)
{
}

int CutebotHeadlight::setHeadlightColor(uint8_t red, uint8_t green, uint8_t blue)
{
    const char buffer[] = {this->headlightId, red, green, blue};
    return this->i2c.write(CUTEBOT_I2C_ADDR, buffer, 4);
}
