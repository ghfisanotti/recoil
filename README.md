# RECOIL
This is a project to measure the recoil of a rifle in order to experiment with different cartridges and
muzzle brakes.

## Components

- Arduino Nano microcontroller to read the value of a potentiometer as it is moved by the recoil of the rifle.

- Raspberry Pi SBC to receive the values acquired by the Arduino, store and display them.

## Communications
Arduino and Raspberry are connected by an I2C bus, Raspberry is master, Arduino is slave.

## Process
Arduino stores pairs of values (time, position of the rifle) for the duration of the recoil. It can store up to 
350 value pairs at a rate of 800 samples/second approximately. 
In order to keep memory usage within the capacity of the Nano, time is stored as a 16-bit unsigned integers 
(microseconds/100). Position is stored as 16-bit unsigned integers (0-1023 range).
Value pairs are kept in-memory in a 350-element array, upon request from the Raspberry the values are sent 
via the I2C bus formatted as a CSV (comma separated values) file, one line per value pair.

A Python process on the Raspberry receives the CSV, stores it as a file on disk and can display graphically 
various collected files for comparison purposes.

CSV files can also be imported into any spreadsheet utility for further analysis.

## Files:

- `*.csv`: CSV files, can be imported to a spread sheet for further analysis
- `*.sh`: shell scripts to execute data capture and display
- `*.gnuplot`: Parameter files for the GNUplot graphics utility
- `*.py`: Raspberry Python code
- `*.ino`: Arduino C++ code

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

