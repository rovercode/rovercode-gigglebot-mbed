#ifndef CUTEBOT_H
#define CUTEBOT_H

#include "inc/drivers/Bot.h"
#include "inc/drivers/cutebot/CutebotHeadlight.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

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
  CutebotMotor* leftMotor;
  CutebotMotor* rightMotor;
  CutebotHeadlight *leftHeadlight;
  CutebotHeadlight *rightHeadlight;

  public:

  Cutebot(MicroBitI2C &_i2c);
  virtual ~Cutebot();
  void setRightMotorPower(int power);
  void setLeftMotorPower(int power);
  void setBothMotorsPower(int power);
  int setLeftHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  int setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  int setBothHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  uint16_t getLeftLineSensorReading();
  uint16_t getRightLineSensorReading();
};

#endif
