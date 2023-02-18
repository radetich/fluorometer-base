#!/usr/bin/env python3
import serial
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)
    ser.reset_input_buffer()
    msg = 'BEGIN TRANSFER\n'
    ser.write(bytes(msg, encoding='utf-8'))
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
    if(line == "GOT BEGIN TRANSFER"):
        print("SYNCED! Waiting...")
        timeout = 300   # [seconds for data collection]
        currtime = time.time()
        while time.time() < currtime + timeout:
            # this will run for timeout seconds and then exit
            time.sleep(1)