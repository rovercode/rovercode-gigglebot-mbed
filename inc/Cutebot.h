#ifndef CUTEBOT_H
#define CUTEBOT_H

// I2C address of the Cutebot
const char I2C_ADDR = 0x10;

// I2C commands for the Cutebot
enum CutebotI2CCommands {
  SET_LEFT_MOTOR_POWER = 1,
  SET_RIGHT_MOTOR_POWER
};
#endif
