Galvanix
********

- `Eclipse setup and misc <https://github.com/Tyrn/arch-chronicle/blob/master/Usage/Ac6_SW4STM32.md>`__

Flash release build
===================

- On ST-Link disconnected from the target:

::

    $ lsusb

- Connect to the target and check:

::

    $ st-info --probe
    ...
    $ st-flash --reset write Release/galvanix.bin 0x08000000
