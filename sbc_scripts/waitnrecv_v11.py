#!/usr/bin/env python3

# PYTHON SERIAL RECEPTION CODE FOR THE BALL AEROSPACE IN WATER FLUOROMETER
# COLE RADETICH 2023
# file should be in /home/control 

# ███████╗██╗     ██╗   ██╗ ██████╗ ██████╗  ██████╗ 
# ██╔════╝██║     ██║   ██║██╔═══██╗██╔══██╗██╔═══██╗
# █████╗  ██║     ██║   ██║██║   ██║██████╔╝██║   ██║
# ██╔══╝  ██║     ██║   ██║██║   ██║██╔══██╗██║   ██║
# ██║     ███████╗╚██████╔╝╚██████╔╝██║  ██║╚██████╔╝
# ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ 


# ╔═╗┌┐┌  ┬┌┐┌  ┬ ┬┌─┐┌┬┐┌─┐┬─┐  ┌─┐┬  ┬ ┬┌─┐┬─┐┌─┐┌┬┐┌─┐┌┬┐┌─┐┬─┐
# ╠═╣│││  ││││  │││├─┤ │ ├┤ ├┬┘  ├┤ │  │ ││ │├┬┘│ ││││├┤  │ ├┤ ├┬┘
# ╩ ╩┘└┘  ┴┘└┘  └┴┘┴ ┴ ┴ └─┘┴└─  └  ┴─┘└─┘└─┘┴└─└─┘┴ ┴└─┘ ┴ └─┘┴└─

# import
import serial
import time
import os
from systemd import journal

#pin16 drives low for our button

#begin...
if __name__ == '__main__':
    with open("/media/usb/data.csv", "a") as dpointer:
        #data batch, open file from USB or create if not there...
        journal.write("Opened data file...")
        #open delay and timeout file from USB to determine how long to wait for
        with open("/media/usb/delay.txt", "r") as fpointer:
            #cast wait time to int
            wait = int(fpointer.read())
            currtime = time.time()
            while time.time() < currtime + wait:
                #stay lowkey until we want to capture data
                pass
            fpointer.close()
            #begin serial handshakes
            with open("/media/usb/timeout.txt", "r") as fpointer:
                #cast wait time to int
                timeout = int(fpointer.read())
                fpointer.close()


                #begin serial handshakes
                ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)

                ser.reset_input_buffer()
                msg = 'BEGIN TRANSFER\n'
                ser.write(bytes(msg, encoding='utf-8'))
                line = ser.readline().decode('utf-8').rstrip()
                if(line == "GOT BEGIN TRANSFER"):
                    dpointer.write('BEGIN BATCH OF DATA, FORMAT BELOW\n\n')
                    dpointer.write('small sensor, large sensor\n')
                    journal.write("Waiting for data from Teensy...")
                    currtime = time.time()
                    while time.time() < currtime + timeout:
                        line = ser.readline().decode('utf-8').rstrip()
                        dpointer.write(line + '\n')
                    #what this says is kinda superfluous since we dont read it
                    #but i like pretty acknowledgements. And it could be helpful for debugging
                    journal.write("Finished processing. Closing file and shutting down...")
                    msg = 'END TRANSFER\n'
                    ser.write(bytes(msg, encoding='utf-8'))


                    ser.close()
                    dpointer.write('\n')
                    dpointer.write('END BATCH OF DATA\n\n')
                    dpointer.close()
                    #we should probably do this somewhere else but for now this + nopwdsudo is the solution
                    os.system('sudo shutdown now')