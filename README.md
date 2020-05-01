# RECOIL MEASUREMENT
This is a project to measure the recoil of a rifle in order to experiment with different cartridges and
muzzle brakes.

## Components

- Arduino Nano microcontroller to read the value of a potentiometer as it is moved by the recoil of the rifle.

- Raspberry Pi SBC to receive the values acquired by the Arduino, store and display them.

- Logic-level converter (2-ports) to connect Raspberry (3.3 volts) I2C bus to Arduino (5 volts) I2C bus,
in theory, as long as the Arduino is configured as slave, it is possible to connect the Raspberry to the Arduino 
with no risk, but that requires to be shure the Arduino is programmed correctly before connecting both devices.
If done incorrectly, you may damage the Raspberry permanently.

## Communications
Arduino and Raspberry are connected by an I2C bus, Raspberry as master, Arduino as slave.

## Process
Arduino stores pairs of values (time, position of the rifle) for the duration of the recoil. It can store up to 
350 value pairs at a rate of 800 samples/second approximately. The recoil event is assumed to last approximately 20 milliseconds.
In order to keep memory usage within the RAM capacity of the Nano (2KB), time is stored as a 16-bit unsigned integers 
(microseconds/100). Position is stored as 16-bit unsigned integers (0-1023 range).
Value pairs are kept in-memory in a 350-element array, upon request from the Raspberry the values are transmitted 
over the I2C bus formatted as a CSV (comma separated values) file, one line per value pair.

A Python process on the Raspberry receives the CSV, stores it as a file on disk and can display graphically 
various collected files for comparison purposes.

CSV files can also be imported into any spreadsheet utility for further analysis.

## Files:

- `*.csv`: CSV files, can be deleted when no longer needed.
- `*.sh`: shell scripts to execute data capture and display.
- `*.gnuplot`: Parameter files for the GNUplot graphics utility.
- `*.py`: Raspberry Python code.
- `*.ino`: Arduino C++ code.

## Pre-requisites:
- Tested on Raspberry Pi 1B/2B/4B with Raspbian Buster.
- Raspberry must have I2C enabled, see raspi-config/Interfacing Options/I2C.
- GNUplot utility, on the Raspberry:

`
	apt install gnuplot
`
- SMbus support for I2C, on the Raspberry:

`
	apt install python-smbus
`

## Usage:
1. Move potentiometer to zero-position, Arduino should turn green LED on, yellow LED off
2. Fire rifle
3. Potentiometer should have moved to max-position, Arduino should turn yellow LED on, green LED off
4. On the Raspberry:

`
	./i2c-read-recoil.sh
`

5. Repeat previous steps as desired
6. To graph the captured data, on the Raspberry:

`
	./plot.sh
`

