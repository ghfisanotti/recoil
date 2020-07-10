# Function: Request CSV file from Arduino on serial port,
#           write each line to standard output
# Author: Gerardo Fisanotti - 8-jul-2020
#
import sys
import serial
import time

ser = serial.Serial(
        port='/dev/ttyUSB0',
        baudrate = 115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=0
      )
so=sys.stdout
se=sys.stderr
retryCnt=0
while 1:
  x=ser.readline()
  if x[0:3]=='END' : break
  so.write(x)
exit
