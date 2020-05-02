# Function: Request CSV file from Arduino on I2C bus,
#           write each line to standar output
# Author: Gerardo Fisanotti - 1-may-2020
#
from smbus import SMBus
import sys
import time

addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1
so=sys.stdout
se=sys.stderr
retryCnt=0
while 1==1 :
  try:
    d = bus.read_i2c_block_data(addr,0,12) # slave addr, ???, bytes to read
    t=""
    for i in range(len(d)) : t+=chr(d[i])
    if t=="     0,    0" : break
    so.write(t + '\n')
  except:
    se.write('I/O error, retrying...\n')
    time.sleep(0.5)
    retryCnt+=1
    if retryCnt>=5: 
      se.write('Aborting...\n')
      exit(1)
exit
