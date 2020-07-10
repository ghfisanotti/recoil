# RECOIL data capture
This is a hardware/software project to measure the recoil of a rifle in order to experiment with different 
cartridges and muzzle brakes.

## Components

- ESP8266 MCU (D1 Mini) to read the values of a potentiometer as it is moved by the recoil of the rifle.

- Raspberry Pi SBC to receive the values acquired by the MCU, store and display them.

## Communications
MCU and Raspberry are connected by USB cable.

## Process
MCU stores pairs of values (time, value of potentiometer) for the duration of the recoil. It can store up to 
1024 value pairs at a rate of 9000 samples/second approximately. The recoil event is assumed to last approximately 20 milliseconds.
Value pairs are kept in-memory in a 1024-element array, after acquiring the last value, all the data is sent
over the USB serial bus formatted as a CSV (comma separated values) file, one line per value pair.

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
- On the Raspberry, change the USB port name on serial-read-recoil.py as required.
- GNUplot utility, on the Raspberry:

`
	apt install gnuplot
`

## Usage:
1. Move potentiometer to zero-position, Arduino should turn green LED on, yellow LED off
2. Fire rifle
3. Potentiometer should have moved to max-position, Arduino should turn yellow LED on, green LED off
4. On the Raspberry:

`
	./serial-read-recoil.sh
`

5. Repeat previous steps as desired
6. To graph the captured data, on the Raspberry:

`
	./plot.sh
`

