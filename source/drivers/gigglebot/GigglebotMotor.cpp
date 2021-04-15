#include "MicroBitEvent.h"

#include "inc/drivers/gigglebot/Gigglebot.h"
#include "inc/drivers/gigglebot/GigglebotMotor.h"

GigglebotMotor::GigglebotMotor(MicroBitI2C &_i2c, GigglebotMotorId _motorId) : i2c(_i2c), motorId(_motorId)
{
}

/**
 * A table for scaling the powers to avoid the lowest values.
 * Scales (-100, -1) to (-100, -36)
 * and (100, 1) to (36, 100).
 * 0 remains 0.
 */
const short int GigglebotMotor::SCALED_POWERS [201] = {
    -100,-99,-99,-98,-97,-97,-96,-95,-95,-94,-94,-93,
    -92,-92,-91,-90,-90,-89,-88,-88,-87,-86,-86,-85,-84,
    -84,-83,-82,-82,-81,-81,-80,-79,-79,-78,-77,-77,-76,
    -75,-75,-74,-73,-73,-72,-71,-71,-70,-69,-69,-68,-68,
    -67,-66,-66,-65,-64,-64,-63,-62,-62,-61,-60,-60,-59,
    -58,-58,-57,-56,-56,-55,-55,-54,-53,-53,-52,-51,-51,
    -50,-49,-49,-48,-47,-47,-46,-45,-45,-44,-43,-43,-42,
    -42,-41,-40,-40,-39,-38,-38,-37,-36,-36,0,36,36,37,
    38,38,39,40,40,41,42,42,43,43,44,45,45,46,47,47,48,
    49,49,50,51,51,52,53,53,54,55,55,56,56,57,58,58,59,
    60,60,61,62,62,63,64,64,65,66,66,67,68,68,69,69,70,
    71,71,72,73,73,74,75,75,76,77,77,78,79,79,80,81,81,
    82,82,83,84,84,85,86,86,87,88,88,89,90,90,91,92,92,
    93,94,94,95,95,96,97,97,98,99,99,100
};

void GigglebotMotor::setMotorPower(int power)
{
    char buffer[3];

    buffer[0] = SET_MOTOR_POWER;
    buffer[1] = this->motorId;
    buffer[2] = SCALED_POWERS[power + 100];

    this->i2c.write(GIGGLEBOT_I2C_ADDR, buffer, 3);
}
