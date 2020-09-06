# Rovercode GiggleBot mBed

The Rovercode service for GiggleBot, written directly on the Lancaster C/C++ mBed micro:bit runtime. Based off [the Lancaster examples](https://github.com/lancaster-university/microbit-samples).
## Setup

* [Install yotta](https://lancaster-university.github.io/microbit-docs/offline-toolchains/#yotta)

##### Alternative Docker image

```
sudo docker build . -t yt
```

## Build

```
yt clean
yt build
```

##### Alternative Docker container

```
sudo docker run --rm -v ${PWD}:/app yt clean
sudo docker run --rm -v ${PWD}:/app yt build
```

## Copy hex to the micro:bit

Example command on Ubuntu.

```bash
cp ./build/bbc-microbit-classic-gcc/source/rovercode-gigglebot-mbed-combined.hex /media/$USER/MICROBIT
```

## Links

* [micro:bit runtime docs](http://lancaster-university.github.io/microbit-docs/)
* [microbit-dal](https://github.com/lancaster-university/microbit-dal)
* [micro:bit](https://github.com/lancaster-university/microbit)
* [yotta docs](http://lancaster-university.github.io/microbit-docs/offline-toolchains/#yotta)

##  microbit-dal configuration

The DAL also contains a number of compile time options can be modified. A full list and explanation
can be found in our [documentation](http://lancaster-university.github.io/microbit-docs/advanced/#compile-time-options-with-microbitconfigh).

Alternately, `yotta` can be used to configure the dal regardless of module/folder structure, through providing a
`config.json` in this directory.

Here is an example of `config.json` with all available options configured:
```json
{
    "microbit-dal":{
        "bluetooth":{
            "enabled": 1,
            "pairing_mode": 1,
            "private_addressing": 0,
            "open": 0,
            "whitelist": 1,
            "advertising_timeout": 0,
            "tx_power": 0,
            "dfu_service": 1,
            "event_service": 1,
            "device_info_service": 1
        },
        "reuse_sd": 1,
        "default_pullmode":"PullDown",
        "gatt_table_size": "0x300",
        "heap_allocator": 1,
        "nested_heap_proportion": 0.75,
        "system_tick_period": 6,
        "system_components": 10,
        "idle_components": 6,
        "use_accel_lsb": 0,
        "min_display_brightness": 1,
        "max_display_brightness": 255,
        "display_scroll_speed": 120,
        "display_scroll_stride": -1,
        "display_print_speed": 400,
        "panic_on_heap_full": 1,
        "debug": 0,
        "heap_debug": 0,
        "stack_size":2048,
        "sram_base":"0x20000008",
        "sram_end":"0x20004000",
        "sd_limit":"0x20002000",
        "gatt_table_start":"0x20001900"
    }
}