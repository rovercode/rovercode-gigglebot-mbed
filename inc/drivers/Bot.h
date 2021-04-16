#ifndef BOT_H
#define BOT_H

#define BOT_ID_BATTERY            500
#define BOT_ID_LIGHT_SENSORS      501
#define BOT_ID_LINE_SENSORS       502

#define BOT_BATTERY_EVT_UPDATE         1
#define BOT_LIGHT_SENSORS_EVT_UPDATE   1
#define BOT_LINE_SENSORS_EVT_UPDATE    1

class Bot {

  bool detected;

  public:

  virtual void setRightMotorPower(int power) = 0;
  virtual void setLeftMotorPower(int power) = 0;
  virtual void setBothMotorsPower(int power) = 0;
  virtual void setLeftHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual void setRightHeadlightColor(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual uint16_t getLeftLightSensorReading() = 0;
  virtual uint16_t getRightLightSensorReading() = 0;
  virtual uint16_t getLeftLineSensorReading() = 0;
  virtual uint16_t getRightLineSensorReading() = 0;
  virtual uint16_t getBatteryVoltage() = 0;

  void setDetected(bool detected) {
    this->detected = detected;
  }

  bool isDetected() {
    return this->detected;
  }
};

#endif
