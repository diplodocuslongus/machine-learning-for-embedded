Arduino IDE code
----

> This code is part of the post series in [here](https://www.stupid-projects.com/posts/machine-learning-on-embedded-part-1/)

This fork is focused on using platformIO, and modification to the code to do benchmark without an oscilloscope (option to use a scope remains).

PlatformIO environments:
a-star32U4
feather52840
teensy41
pico

(other are not yet tested)

The (slightly) modifed code has been tested on a pololu a-star32U4, 16MHz and a teensy41, 600MHz

Timing result 
a-star32U4
NN 2 (with hidden layer)
Average inference time: 5680.57us / inference
Total for 1000 predictions:5680568us

teensy41
NN 2
Average inference time: 10.04us / inference
Total for 1000 predictions:10.40ms (measured in terms of CPU cycles)

adafruit_feather_nrf52840
Average inference time: 622.07us / inference
Total for 1000 predictions:622071us


For the timing of the teensy I used 
https://forum.pjrc.com/threads/61561-Teensy-4-Global-vs-local-variables-speed-of-execution?highlight=execution
/C_CPU_ACTUAL
Original README:

The code is tested with the following MCUs:

* Arduino UNO
* Arduino nano
* Arduino mini
* Arduino Leonardo
* Teensy 3.2
* Teensy 3.5

## Instructions
To build the project open Arduino IDE and then load the `code-arduino.ino`
code file, build and upload. In case of the Teensy boards you can also
overclock to the maximum frequencies.

## Libraries
To build this code you need the TimerOne library. Just install it from
the Library manager in the arduino IDE. The version I've used is 1.0.1.

In case of Teensy 3.5 there's a conflict for the TimerOne lib from the
library manager as the board package comes with that integrated for the
specific MCU. In this case you need to uninstall the previous (just delete
the folder with the library) and build.

## Versions
Arduino IDE: 1.8.9
TimerOne: 1.0.1
