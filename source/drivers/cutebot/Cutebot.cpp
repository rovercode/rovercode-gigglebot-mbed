#include "MicroBit.h"
#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotHeadlight.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

Cutebot::Cutebot(MicroBitI2C &_i2c) : i2c(_i2c) {
    this->leftHeadlight = new CutebotHeadlight(i2c, CUTEBOT_HEADLIGHT_ID_LEFT);
    this->rightHeadlight = new CutebotHeadlight(i2c, CUTEBOT_HEADLIGHT_ID_RIGHT);

    int result = this->setBothHeadlightColor(0, 0, 0);
    if (result == MICROBIT_OK) {
        this->setDetected(true);
    } else {
        this->setDetected(false);
    }

    this->leftMotor = new CutebotMotor(i2c,  CUTEBOT_MOTOR_ID_LEFT);
    this->rightMotor = new CutebotMotor(i2c,  CUTEBOT_MOTOR_ID_RIGHT);
    /* TODO: Add sensors */
}

Cutebot::~Cutebot() {
    delete this->leftMotor;
    delete this->rightMotor;
    delete this->leftHeadlight;
    delete this->rightHeadlight;
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
    return this->leftHeadlight->setHeadlightColor(red, green, blue);
}

int Cutebot::setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) {
    return this->rightHeadlight->setHeadlightColor(red, green, blue);
}

int Cutebot::setBothHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) {
    this->leftHeadlight->setHeadlightColor(red, green, blue);
    return this->rightHeadlight->setHeadlightColor(red, green, blue);
}

uint16_t Cutebot::getLeftLineSensorReading() {
    /* TODO */
    return 0;
}

uint16_t Cutebot::getRightLineSensorReading() {
    /* TODO */
    return 0;
}
