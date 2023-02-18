#!/usr/bin/env python3

# file should be in /home/control 

# import
import serial
import time
import os

#sigint should send END TRANSFER? such that we dont ever leave the teensy on

#OS shutting off probably also should send a END TRANSFER message just in case. Cant hurt. Implement via hook


timeout = 300   # [seconds for data collection]

#begin...
if __name__ == '__main__':
    with open("/media/usb/data.txt", "a") as dpointer:
        #debug ip printout. This is for the idea forge. DONT leave this in production
        os.system('ip addr > /media/usb/ip.txt')
        #data batch
        dpointer.write('BEGIN BATCH OF DATA\n\n\n')
        #open delay file from USB to determine how long to wait for
        with open("/media/usb/delay.txt", "r") as fpointer:
            #cast wait time to int
            wait = int(fpointer.read())
            currtime = time.time()
            while time.time() < currtime + wait:
                #stay lowkey until we want to capture data
                pass
            fpointer.close()
            #begin serial handshakes
            ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)

            #end any mishandled transfers well..
            msg = 'END TRANSFER\n'
            ser.write(bytes(msg, encoding='utf-8'))
            ser.reset_input_buffer()
            msg = 'BEGIN TRANSFER\n'
            ser.write(bytes(msg, encoding='utf-8'))
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            while(line != "GOT BEGIN TRANSFER"):
                pass
            if(line == "GOT BEGIN TRANSFER"):
                print("SYNCED! Waiting for data...")
                currtime = time.time()
                while time.time() < currtime + timeout:
                    # this will run for timeout seconds and then exit
                    # work in progress
                    line = ser.readline().decode('utf-8').rstrip()
                    dpointer.write(line + '\n')
                    print(line)
                #what this says is kinda superfluous since we dont read it
                #but i like pretty acknowledgements. And it could be helpful for debugging
                msg = 'END TRANSFER\n'
                ser.write(bytes(msg, encoding='utf-8'))

                dpointer.write('END BATCH OF DATA\n\n\n')
                dpointer.close()