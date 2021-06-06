#ifndef CUTEBOT_H
#define CUTEBOT_H

#include "inc/drivers/Bot.h"
#include "inc/drivers/cutebot/CutebotHeadlight.h"
#include "inc/drivers/cutebot/CutebotMotor.h"
#include "inc/drivers/cutebot/CutebotLineSensors.h"
#include "inc/drivers/cutebot/CutebotDistanceSensor.h"

// Reference: https://github.com/elecfreaks/pxt-cutebot

#define CUTEBOT_PERIOD_LINE_SENSORS          500
#define CUTEBOT_START_COUNT_LINE_SENSORS     300
#define CUTEBOT_PERIOD_DISTANCE_SENSOR       500
#define CUTEBOT_START_COUNT_DISTANCE_SENSOR  100

// I2C address of the Cutebot
const char CUTEBOT_I2C_ADDR = 0x10 << 1;

// I2C commands for the Cutebot
enum CutebotI2CCommands {
  SET_LEFT_MOTOR_POWER = 1,
  SET_RIGHT_MOTOR_POWER,
  SET_LEFT_HEADLIGHT = 4,
  SET_RIGHT_HEADLIGHT = 8,
};

class Cutebot : public Bot
{
  MicroBitI2C &i2c;
  MicroBitIO &io;
  CutebotMotor* leftMotor;
  CutebotMotor* rightMotor;
  CutebotHeadlight *leftHeadlight;
  CutebotHeadlight *rightHeadlight;
  CutebotLineSensors *lineSensors;
  CutebotDistanceSensor *distanceSensor;

  public:

  Cutebot(MicroBitI2C &_i2c, MicroBitIO &_io);
  virtual ~Cutebot();
  void setRightMotorPower(int power);
  void setLeftMotorPower(int power);
  void setBothMotorsPower(int power);
  int setLeftHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  int setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  int setBothHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  uint16_t getLeftLineSensorReading();
  uint16_t getRightLineSensorReading();
  uint16_t getDistanceSensorReading();
};

#endif
