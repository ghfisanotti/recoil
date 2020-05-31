# RECOIL data capture
This is a hardware/software project to measure the recoil of a rifle in order to experiment with different 
cartridges and muzzle brakes.

## Components

- ESP8266 MCU (D1 Mini) to read the values of a potentiometer as it is moved by the recoil of the rifle.

- Raspberry Pi SBC to receive the values acquired by the MCU, store and display them.

## Communications
MCU and Raspberry are connected by an I2C bus, Raspberry as master, MCU as slave.

## Process
MCU stores pairs of values (time, value of potentiometer) for the duration of the recoil. It can store up to 
1024 value pairs at a rate of 9000 samples/second approximately. The recoil event is assumed to last approximately 20 milliseconds.
Value pairs are kept in-memory in a 1024-element array, upon request from the Raspberry the values are transmitted 
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
- On the Raspberry, the following lines must be added to the end of /boot/config.txt

```
dtparam=i2c1_baudrate=30000 #GHF I2C speed
core_freq=250 #GHF I2C clock stability issue
```

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

