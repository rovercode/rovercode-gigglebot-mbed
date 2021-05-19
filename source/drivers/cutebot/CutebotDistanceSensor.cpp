#include "MicroBit.h"
#include "MicroBitEvent.h"

#include "inc/drivers/cutebot/Cutebot.h"
#include "inc/drivers/cutebot/CutebotDistanceSensor.h"

CutebotDistanceSensor::CutebotDistanceSensor(MicroBitIO &_io) : io(_io), distance(0),
    counter(CUTEBOT_PERIOD_DISTANCE_SENSOR - CUTEBOT_START_COUNT_DISTANCE_SENSOR)
{
    io.P8.setPull(PullNone);
}

uint16_t CutebotDistanceSensor::getDistance()
{
    return this->distance;
}

uint64_t measurePulseWidthMicroSecs(MicroBitPin* pin) {
    // Reference: https://github.com/microsoft/pxt-microbit/blob/ae464ddbb386f077aad08894d03afae3e9f0d917/libs/core/pins.cpp#L253

#if MICROBIT_CODAL //  for V2 micro:bit
        // set polarity
        pin->setPolarity(PulseValue::High == value ? 1 : 0);
        // record pulse
        int period = pin->getPulseUs(maxDuration);
        // timeout
        if (DEVICE_CANCELLED == period)
            return 0;
        // success!
        return period;
#else
        int pulse = 1;  // Measure high
        uint64_t tick =  system_timer_current_time_us();
        uint64_t maxd = 25000;
        while(pin->getDigitalValue() != pulse) {
            if(system_timer_current_time_us() - tick > maxd)
                return 0;
        }

        uint64_t start =  system_timer_current_time_us();
        while(pin->getDigitalValue() == pulse) {
            if(system_timer_current_time_us() - tick > maxd)
                return 0;
        }
        uint64_t end =  system_timer_current_time_us();
        return end - start;
#endif
}

void CutebotDistanceSensor::idleTick()
{
    if (++counter < CUTEBOT_PERIOD_DISTANCE_SENSOR)
    {
        return;
    }

    counter = 0;

    // send pulse
    io.P8.setDigitalValue(0);
    wait_us(2);
    io.P8.setDigitalValue(1);
    wait_us(10);
    io.P8.setDigitalValue(0);
    // read pulse
    uint64_t pulseWidth = measurePulseWidthMicroSecs(&io.P12);
    this->distance = pulseWidth * 9 / 6 / 58;
    MicroBitEvent e(BOT_ID_DISTANCE_SENSOR, BOT_DISTANCE_SENSOR_EVT_UPDATE);
}
