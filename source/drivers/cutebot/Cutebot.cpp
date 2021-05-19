#include "MicroBit.h"
#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotHeadlight.h"
#include "inc/drivers/cutebot/CutebotMotor.h"
#include "inc/drivers/cutebot/CutebotLineSensors.h"
#include "inc/drivers/cutebot/CutebotDistanceSensor.h"

Cutebot::Cutebot(MicroBitI2C &_i2c, MicroBitIO &_io) : i2c(_i2c), io(_io) {
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

    this->lineSensors = new CutebotLineSensors(io);
    this->distanceSensor = new CutebotDistanceSensor(io);
    fiber_add_idle_component(lineSensors);
    fiber_add_idle_component(distanceSensor);
}

Cutebot::~Cutebot() {
    delete this->leftMotor;
    delete this->rightMotor;
    delete this->leftHeadlight;
    delete this->rightHeadlight;
    delete this->lineSensors;
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
    return this->lineSensors->getLeftReading();
}

uint16_t Cutebot::getRightLineSensorReading() {
    return this->lineSensors->getRightReading();
}

uint16_t Cutebot::getDistanceSensorReading() {
    return this->distanceSensor->getDistance();
}

