#thanks santo
#Cole Radetich 2023

import time
import serial     
import datetime     


if __name__ == '__main__':
    teensy = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    teensy.reset_input_buffer()
    while True:
        if teensy.in_waiting > 0:
            line = teensy.readline().decode('utf-8').rstrip()
            print(line)