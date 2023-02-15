#thanks santo
#Cole Radetich 2023

import time
import serial     
import datetime     


teensy = serial.Serial(
	port='/dev/ttyAMA0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)
counter=0
                
while 1:
    x=teensy.readline()
    print(x)