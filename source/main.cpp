#include "MicroBit.h"
#include "MicroBitUARTService.h"

MicroBit uBit;
MicroBitUARTService *uart;

const MicroBitImage IMAGE_HAPPY = MicroBitImage("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");  

int connected = 0;

void onConnected(MicroBitEvent)
{
    uBit.display.print(IMAGE_HAPPY);
    connected = 1;
    uart->eventOn(ManagedString("\n"), ASYNC);
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
        msg = uart->readUntil(ManagedString("\n"));
        uBit.display.scrollAsync(msg);
        uBit.display.print(IMAGE_HAPPY);
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
    uart->send(ManagedString("YES"));
    uBit.display.scroll("Y");
}

void onButtonB(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uart->send(ManagedString("NO"));
    uBit.display.scroll("N");
}

void onButtonAB(MicroBitEvent)
{
    if (connected == 0)
    {
        return;
    }
    uart->send(ManagedString("GOT IT!!"));
    uBit.display.scroll("!");
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
    uart->send(buffer);
}


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    // uBit.accelerometer.setPeriod(1000);  // In case you want to slow it down. Defaults to 20ms.

    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onButtonAB);
    uBit.messageBus.listen(MICROBIT_ID_BLE_UART, MICROBIT_BLE_EVENT_SERVICE, onUartEvent);
    uBit.messageBus.listen(MICROBIT_ID_ACCELEROMETER, MICROBIT_ACCELEROMETER_EVT_DATA_UPDATE, onNewAccelData);

    // Note GATT table size increased from default in MicroBitConfig.h
    // #define MICROBIT_SD_GATT_TABLE_SIZE             0x500
    uart = new MicroBitUARTService(*uBit.ble, 32, 32);

    uBit.display.print("R");
    uBit.sleep(2000);
    uBit.display.scrollAsync(microbit_friendly_name());
    uBit.display.print("R");


    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}
