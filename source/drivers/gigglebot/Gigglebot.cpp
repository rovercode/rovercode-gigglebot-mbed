#include "MicroBit.h"
#include "inc/drivers/gigglebot/Gigglebot.h"
#include "inc/drivers/gigglebot/GigglebotMotor.h"
#include "inc/drivers/gigglebot/GigglebotBattery.h"
#include "inc/drivers/gigglebot/GigglebotLightSensors.h"
#include "inc/drivers/gigglebot/GigglebotLineSensors.h"

Gigglebot::Gigglebot(MicroBitI2C &i2c) {
    char buffer[2];
    int result = i2c.read(GIGGLEBOT_I2C_ADDR, buffer, 2);
    if (result == MICROBIT_OK) {
        this->setDetected(true);
    } else {
        this->setDetected(false);
    }

    this->leftMotor = new GigglebotMotor(i2c,  GIGGLEBOT_MOTOR_ID_LEFT);
    this->rightMotor = new GigglebotMotor(i2c,  GIGGLEBOT_MOTOR_ID_RIGHT);
    this->bothMotors = new GigglebotMotor(i2c,  GIGGLEBOT_MOTOR_ID_BOTH);
    this->lineSensors = new GigglebotLineSensors(i2c);
    this->lightSensors = new GigglebotLightSensors(i2c);
    this->battery = new GigglebotBattery(i2c);
    fiber_add_idle_component(lineSensors);
    fiber_add_idle_component(lightSensors);
    fiber_add_idle_component(battery);
}

Gigglebot::~Gigglebot() {
    fiber_remove_idle_component(lineSensors);
    fiber_remove_idle_component(lightSensors);
    fiber_remove_idle_component(battery);
    delete this->leftMotor;
    delete this->rightMotor;
    delete this->bothMotors;
    delete this->lineSensors;
    delete this->lightSensors;
    delete this->battery;
}

void Gigglebot::setRightMotorPower(int power) {
    this->rightMotor->setMotorPower(power);
}

void Gigglebot::setLeftMotorPower(int power) {
    this->leftMotor->setMotorPower(power);
}

void Gigglebot::setBothMotorsPower(int power) {
    this->bothMotors->setMotorPower(power);
}

uint16_t Gigglebot::getLeftLightSensorReading() {
    return this->lightSensors->getLeftReading();
}

uint16_t Gigglebot::getRightLightSensorReading() {
    return this->lightSensors->getRightReading();
}

uint16_t Gigglebot::getLeftLineSensorReading() {
    return this->lineSensors->getLeftReading();
}

uint16_t Gigglebot::getRightLineSensorReading() {
    return this->lineSensors->getRightReading();
}

uint16_t Gigglebot::getBatteryVoltage() {
    return this->battery->getVoltage();
}