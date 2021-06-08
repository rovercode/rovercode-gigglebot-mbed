#include "MicroBitEvent.h"

#include "inc/drivers/gigglebot/Gigglebot.h"
#include "inc/drivers/gigglebot/GigglebotLineSensors.h"

GigglebotLineSensors::GigglebotLineSensors(MicroBitI2C &_i2c)
    : i2c(_i2c), readings{0, 0}, counter(GIGGLEBOT_PERIOD_LINE_SENSORS -
                                         GIGGLEBOT_START_COUNT_LINE_SENSORS) {}

uint16_t GigglebotLineSensors::getLeftReading() { return this->readings[1]; }

uint16_t GigglebotLineSensors::getRightReading() { return this->readings[0]; }

void GigglebotLineSensors::idleTick() {
  char command = GET_LINE_SENSORS;
  char buffer[3];

  if (++counter < GIGGLEBOT_PERIOD_LINE_SENSORS) {
    return;
  }

  counter = 0;

    this->i2c.write(GIGGLEBOT_I2C_ADDR, &command, 1);
    this->i2c.read(GIGGLEBOT_I2C_ADDR, buffer, 3);
    for (int i=0; i<2; i++) {
        this->readings[i] = buffer[i] << 2;
        this->readings[i] |= ((buffer[2] << (i * 2)) & 0xC0) >> 6;
        this->readings[i] = 1023 - this->readings[i];
    }

    MicroBitEvent e(BOT_ID_LINE_SENSORS, BOT_LINE_SENSORS_EVT_UPDATE);
}
