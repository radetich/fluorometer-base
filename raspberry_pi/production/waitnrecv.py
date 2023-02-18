#!/usr/bin/env python3

# file should be in /home/control 

# import
import serial
import time


#begin...
if __name__ == '__main__':

    #open delay file from USB to determine how long to wait for
    with open("/media/usb/delay.txt", "r") as fpointer:
        #cast wait time to int
        wait = int(fpointer.read())
        currtime = time.time()
        while time.time() < currtime + wait:
            #stay lowkey until we want to capture data
            pass
        
        #begin serial handshakes
        ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)
        ser.reset_input_buffer()
        msg = 'BEGIN TRANSFER\n'
        ser.write(bytes(msg, encoding='utf-8'))
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        if(line == "GOT BEGIN TRANSFER"):
            print("SYNCED! Waiting...")
            while(1):
                line = ser.readline().decode('utf-8').rstrip()
                print(line)

                
            #timeout = 300   # [seconds for data collection]
            #currtime = time.time()
            #while time.time() < currtime + timeout:
                # this will run for timeout seconds and then exit
            #    time.sleep(1)