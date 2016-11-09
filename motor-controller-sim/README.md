# Motor Controller Simulator

This program simulates the kangaroo motor controller for a left and right motor.

## Wiring

This code assumes the left motor is connected to pin 3, and right motor to pin
4.

## Kangaroo Commands

### General

All commands to the Kangaroo must end with both a carriage return and new line.
All responses are delimited by both as well.

Commands are sent in the format
```
<channel #>,<command>
```

In this case, `channel #` is `1` for the left motor and `2` for the right motor.

### Setup

The `start` and `home` commands must be issued to every motor before any other
command. Failure to do so will return `E1` or `E2`, corresponding to "not
started" and "not homed".
```
1,start
2,start
1,home
2,home
```

### Commands

The following is a list of commands supported by this simulator:
- start
- home
- s - Set the speed of a motor
- getp (TODO) - Get the encoder count of a motor

## Other

A detailed documentation and other commands can be found in the Kangaroo
[manual](https://www.dimensionengineering.com/datasheets/KangarooManual.pdf)
(starting on page 11).

See the [R2Bot Wheel Controller](https://github.com/cornell-cup/cs-r2-bot/blob/master/R2Bot/R2Bot/src/WheelController.cpp)
and [Motor Controller](https://github.com/cornell-cup/cs-r2-bot/blob/master/R2Bot/R2Bot/src/MotorController.cpp)
for examples.
