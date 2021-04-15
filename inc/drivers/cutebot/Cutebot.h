#ifndef CUTEBOT_H
#define CUTEBOT_H

#include "inc/drivers/Bot.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

// I2C address of the Cutebot
const char CUTEBOT_I2C_ADDR = 0x10;

// I2C commands for the Cutebot
enum CutebotI2CCommands {
  SET_LEFT_MOTOR_POWER = 1,
  SET_RIGHT_MOTOR_POWER
};

class Cutebot : public Bot
{
  CutebotMotor* leftMotor;
  CutebotMotor* rightMotor;

  public:

  Cutebot(MicroBitI2C &_i2c);
  void setRightMotorPower(int power);
  void setLeftMotorPower(int power);
  void setBothMotorsPower(int power);
  void setLeftHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  void setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue);
  uint16_t getLeftLightSensorReading();
  uint16_t getRightLightSensorReading();
  uint16_t getLeftLineSensorReading();
  uint16_t getRightLineSensorReading();
  uint16_t getBatteryVoltage();
};

#endif
