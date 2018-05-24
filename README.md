# FornoUV

## Dependencies
[Adafruit Sensor](https://github.com/adafruit/Adafruit_Sensor)

## Description

### Usage logic

* POWER ON: It turns on a green light.
* SELECTING TIME: It enters into the state pressing the button BTNTIME+ or BTNTIME- and releasing it. It returns in the base state pressing and releasing the button BTNSTART.
Buttons work:
  * Click less than one second: increments/decreases by one minute;
  * Click more than one second: increments/decreases by a number of seconds as the duration of the pression.
* START WORK: From the base state, pressing the BTNSTART it starts the work. The servomotor self move in closed position and, when it arrives to position, will be turned on the work red light, the UV leds and the internal engine. The work continues until the time ends or the button STOP has been pressed. The button STOP resets the UV oven (turns off the red light, the internal engine, the UV leds and take the servomotor to the open position and at last turns on the green light).
* POWER OFF

## Folders FornoUV

This folder contains all the code of the sketch. This code has to be uploaded to the Arduino board into the UV oven.
