#include "MicroBit.h"
#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

Cutebot::Cutebot(MicroBitI2C &_i2c) : i2c(_i2c) {
    int result = this->setRightHeadlightColor(0, 0, 0);
    if (result == MICROBIT_OK) {
        this->setDetected(true);
    } else {
        this->setDetected(false);
    }

    if (this->isDetected()) {
        this->leftMotor = new CutebotMotor(i2c,  CUTEBOT_MOTOR_ID_LEFT);
        this->rightMotor = new CutebotMotor(i2c,  CUTEBOT_MOTOR_ID_RIGHT);
        /* TODO: Add sensors */
    }
}

void Cutebot::setRightMotorPower(int power) {
    this->rightMotor->setMotorPower(power);
}

void Cutebot::setLeftMotorPower(int power) {
    this->leftMotor->setMotorPower(power);
}

void Cutebot::setBothMotorsPower(int power) {
    this->rightMotor->setMotorPower(power);
    this->leftMotor->setMotorPower(power);
}

int Cutebot::setLeftHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) {
    const char buffer[] = {SET_LEFT_HEADLIGHT, red, green, blue};
    int result = this->i2c.write(CUTEBOT_I2C_ADDR, buffer, 4);
    return result;
}

int Cutebot::setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) {
    const char buffer[] = {SET_RIGHT_HEADLIGHT, red, green, blue};
    int result = this->i2c.write(CUTEBOT_I2C_ADDR, buffer, 4);
    return result;
}

uint16_t Cutebot::getLeftLineSensorReading() {
    /* TODO */
    return 0;
}

uint16_t Cutebot::getRightLineSensorReading() {
    /* TODO */
    return 0;
}
