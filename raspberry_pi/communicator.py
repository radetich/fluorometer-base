#!/usr/bin/env python3
import serial
import time
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    ser.reset_input_buffer()
    while True:
        msg = input("Enter your message: ")
        msg = msg + '\n'
        ser.write(bytes(msg, encoding='utf-8'))
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)

