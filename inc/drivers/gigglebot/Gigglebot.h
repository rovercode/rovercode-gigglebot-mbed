#ifndef GIGGLEBOT_H
#define GIGGLEBOT_H

#include "inc/drivers/Bot.h"
#include "inc/drivers/gigglebot/GigglebotMotor.h"
#include "inc/drivers/gigglebot/GigglebotLightSensors.h"
#include "inc/drivers/gigglebot/GigglebotLineSensors.h"
#include "inc/drivers/gigglebot/GigglebotBattery.h"

// I2C address of the Gigglebot
const char GIGGLEBOT_I2C_ADDR = 0x04 << 1;

// I2C commands for the Gigglebot
enum GigglebotI2CCommands {
  GET_FIRMWARE_VERSION = 1,
  GET_MANUFACTURER,
  GET_BOARD,
  GET_VOLTAGE_BATTERY,
  GET_LINE_SENSORS,
  GET_LIGHT_SENSORS,
  GET_MOTOR_STATUS_RIGHT,
  GET_MOTOR_STATUS_LEFT,
  SET_MOTOR_POWER,
  SET_MOTOR_POWERS
};

#define GIGGLEBOT_PERIOD_BATTERY            1000
#define GIGGLEBOT_START_COUNT_BATTERY       50
#define GIGGLEBOT_PERIOD_LIGHT_SENSORS      500
#define GIGGLEBOT_START_COUNT_LIGHT_SENSORS 200
#define GIGGLEBOT_PERIOD_LINE_SENSORS       500
#define GIGGLEBOT_START_COUNT_LINE_SENSORS  300

class Gigglebot : public Bot
{
  GigglebotMotor* leftMotor;
  GigglebotMotor* rightMotor;
  GigglebotMotor* bothMotors;
  GigglebotLineSensors* lineSensors;
  GigglebotLightSensors* lightSensors;
  GigglebotBattery* battery;

  public:

  Gigglebot(MicroBitI2C &_i2c);
  virtual ~Gigglebot();
  void setRightMotorPower(int power);
  void setLeftMotorPower(int power);
  void setBothMotorsPower(int power);
  uint16_t getLeftLightSensorReading();
  uint16_t getRightLightSensorReading();
  uint16_t getLeftLineSensorReading();
  uint16_t getRightLineSensorReading();
  uint16_t getBatteryVoltage();
};

#endif
