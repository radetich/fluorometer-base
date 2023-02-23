#!/usr/bin/env python3

# file should be in /home/control 

# import
import serial

#begin...
if __name__ == '__main__':
        ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)

        #end any mishandled transfers well..
        msg = 'END TRANSFER\n'
        ser.write(bytes(msg, encoding='utf-8'))
        ser.reset_input_buffer()

        ser.close()