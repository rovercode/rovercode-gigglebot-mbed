#ifndef GIGGLEBOT_H
#define GIGGLEBOT_H

// I2C address of the Gigglebot
const char I2C_ADDR = 0x04 << 1;

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

#define GIGGLEBOT_ID_BATTERY            500

#endif