#include "MicroBit.h"
#include "MicroBitUARTService.h"

#include "inc/drivers/Bot.h"
#include "inc/drivers/gigglebot/Gigglebot.h"
#include "inc/drivers/cutebot/Cutebot.h"

MicroBit uBit;
MicroBitUARTService *uart;

Bot* bot;

const MicroBitImage IMAGE_HAPPY = MicroBitImage("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");

int connected = 0;

void onConnected(MicroBitEvent)
{
    uBit.display.print(IMAGE_HAPPY);
    connected = 1;
    uart->eventOn(ManagedString("\n"), ASYNC);
}

void handleDisplay()
{
    ManagedString msg = uart->readUntil(ManagedString("\n"));
    uBit.display.printAsync(msg, 500);
    uBit.display.print(IMAGE_HAPPY);
}

void handleRightMotor()
{
    ManagedString msg = uart->readUntil(ManagedString("\n"));
    bot->setRightMotorPower(atoi(msg.toCharArray()));
}

void handleLeftMotor()
{
    ManagedString msg = uart->readUntil(ManagedString("\n"));
    bot->setLeftMotorPower(atoi(msg.toCharArray()));
}

void handleBothMotors()
{
    ManagedString msg = uart->readUntil(ManagedString("\n"));
    bot->setBothMotorsPower(atoi(msg.toCharArray()));
}

void onUartEvent(MicroBitEvent)
{
    ManagedString msg = uart->readUntil(ManagedString(":"), ASYNC);
    if (msg.length() == 0)
    {
        // Invalid command. Throw out rx buffer.
        uart->readUntil(ManagedString("\n"));
        return;
    }

    if (msg == "disp")
    {
        create_fiber(handleDisplay);
    }
    else if (msg == "right-motor") {
        create_fiber(handleRightMotor);
    }
    else if (msg == "left-motor") {
        create_fiber(handleLeftMotor);
    }
    else if (msg == "both-motors") {
        create_fiber(handleBothMotors);
    }
    else
    {
        // Unknown command. Throw out rx buffer.
        uart->readUntil(ManagedString("\n"));
    }
}

void onDisconnected(MicroBitEvent)
{
    uBit.display.print("R");
    connected = 0;
}

void onButtonA(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uart->send(ManagedString("button:a"), ASYNC);
}

void onButtonB(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uart->send(ManagedString("button:b"), ASYNC);
}

void onNewAccelData(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uBit.sleep(1);  // Prevents an 020 error. 🤷
    Sample3D sample = uBit.accelerometer.getSample();
    char buffer[20];
    snprintf(buffer, 20, "accel:%d,%d,%d", sample.x, sample.y, sample.z);
    uart->send(buffer, ASYNC);
}

void onNewBatteryData(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uBit.sleep(1);  // Prevents an 020 error. 🤷
    char buffer[20];
    snprintf(buffer, 20, "battery-sens:%d", bot->getBatteryVoltage());
    uart->send(buffer, ASYNC);
}

void onNewLightSensorsData(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uBit.sleep(1);  // Prevents an 020 error. 🤷
    char buffer[23];
    snprintf(buffer, 23, "light-sens:%d,%d", bot->getLeftLightSensorReading(), bot->getRightLightSensorReading());
    uart->send(buffer, ASYNC);
}

void onNewLineSensorsData(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uBit.sleep(1);  // Prevents an 020 error. 🤷
    char buffer[23];
    snprintf(buffer, 23, "line-sens:%d,%d", bot->getLeftLineSensorReading(), bot->getRightLineSensorReading());
    uart->send(buffer, ASYNC);
}


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    bot = new Gigglebot(uBit.i2c);
    if (!bot->isDetected()) {
        delete bot;
        bot = new Cutebot(uBit.i2c, uBit.io);
        if (!bot->isDetected()) {
            delete bot;
            uBit.display.scrollAsync("NO BOT");
        }
    }

    uBit.accelerometer.setPeriod(1000);  // milliseconds

    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BLE_UART, MICROBIT_BLE_EVENT_SERVICE, onUartEvent);
    // uBit.messageBus.listen(MICROBIT_ID_ACCELEROMETER, MICROBIT_ACCELEROMETER_EVT_DATA_UPDATE, onNewAccelData);
    uBit.messageBus.listen(BOT_ID_BATTERY, BOT_BATTERY_EVT_UPDATE, onNewBatteryData);
    uBit.messageBus.listen(BOT_ID_LIGHT_SENSORS, BOT_LIGHT_SENSORS_EVT_UPDATE, onNewLightSensorsData);
    uBit.messageBus.listen(BOT_ID_LINE_SENSORS, BOT_LINE_SENSORS_EVT_UPDATE, onNewLineSensorsData);

    // Note GATT table size increased from default in MicroBitConfig.h
    // #define MICROBIT_SD_GATT_TABLE_SIZE             0x500
    uart = new MicroBitUARTService(*uBit.ble, 32, 128);

    uBit.display.print("R");
    uBit.sleep(2000);
    uBit.display.scrollAsync(microbit_friendly_name());
    uBit.display.print("R");

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}
