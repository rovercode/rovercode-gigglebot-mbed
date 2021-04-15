#include "MicroBit.h"
#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotMotor.h"

Cutebot::Cutebot(MicroBitI2C &i2c) {
    /* TODO: Try to read something on the Cutebot to determine if it's present */
    this->setDetected(false);

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

void Cutebot::setLeftHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) {
    /* TODO */
    return;
}

void Cutebot::setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) {
    /* TODO */
    return;
}

uint16_t Cutebot::getLeftLightSensorReading() {
    /* Not implemented on this bot */
    return 0;
}

uint16_t Cutebot::getRightLightSensorReading() {
    /* Not implemented on this bot */
    return 0;
}

uint16_t Cutebot::getLeftLineSensorReading() {
    /* TODO */
    return 0;
}

uint16_t Cutebot::getRightLineSensorReading() {
    /* TODO */
    return 0;
}

uint16_t Cutebot::getBatteryVoltage() {
    /* Not implemented on this bot */
    return 0;
}