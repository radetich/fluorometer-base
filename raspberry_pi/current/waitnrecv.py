#!/usr/bin/env python3

# file should be in /home/control 

# import
import serial
import time
import socket   

#this is for the idea forge. It forces a change in my hostname so unless I want to connect a screen I have to get the IP this way
ip = 0
if(socket.gethostname()):
    hostname=socket.gethostname()   
    ip=socket.gethostbyname(hostname)   
    print("CURR HOSTNAME:"+hostname)   
    print("CURR IPADDR:"+ip)

timeout = 300   # [seconds for data collection]

#begin...
if __name__ == '__main__':
    with open("/media/usb/data.txt", "a") as dpointer:
        dpointer.write('IP ADDR\n')
        dpointer.write(str(ip) + "\n")
        dpointer.write('BEGIN DATA\n')
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
            ser.reset_input_buffer()
            msg = 'BEGIN TRANSFER\n'
            ser.write(bytes(msg, encoding='utf-8'))
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
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

                dpointer.close()