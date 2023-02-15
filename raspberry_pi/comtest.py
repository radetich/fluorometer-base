#thanks santo
#Cole Radetich 2023


"""


This actually doesn't apply to us since we are running no gui. Remove later once baud is sorted.
By default, the Raspberry Pi uses the UART as a serial console. Before using UART, make sure that 
/dev/ttyAMA0 is not being used as a console. This can be done by changing the boot command line by 
editing the /boot/cmdline.txt file and removing the line "console=ttyAMA0,115200 kgdboc=ttyAMA0,115200" 
from the boot arguments. Also, comment out the following line: "2:23:respawn:/sbin/getty -L ttyAMA0 115200 vt100" 
in the file /etc/inittab.

In the case when the /boot is mounted as a read-only partition, it must be 
remounted with write permissions to enable modifying the cmdline.txt file.

sudo mount -n -o remount,rw /boot
Then edit the cmdline.txt file and reboot the Raspberry Pi board.

By default, the pi user is in the dialout group. That gives pi the ability to access 
/dev/ttyAMA0 (and, consequently, UART from Java) without administrator rights.

The UARTConfig.controllerNumber value is an index of the port in the array of port names 
obtained from the microedition.commports property. The microedition.commports property is platform-specific.

In a Linux environment, the microedition.commports property lists the devices, filtered by 
using the deviceaccess.uart.prefix property. The deviceaccess.uart.prefix property in the jwc_properties.ini file contains a list of prefixes separated with a space. If there are 4 serial ports available on a Linux system such as /dev/ttyAMA0, /dev/ttyUSB1, /dev/ttyUSB2, and /dev/ttyCusom0 and deviceaccess.uart.prefix=ttyAMA ttyUSB, then the microedition.commports property contains ttyAMA0, ttyUSB0, and ttyUSB1, in a different order maybe. The actual order depends on the dedicated operating system file structure. To find out the real order of devices on Linux, use the ls -f/dev command.

The following parameters are supported in an ad-hoc configuration:

baudRate - 110, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200

dataBits - 7, 8

parity - PARITY_ODD, PARITY_EVEN, PARITY_NONE

stopBits - 1, 2

flowcontrol - FLOWCONTROL_NONE



"""



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
    now=datetime.datetime.now()
    y=now.strftime("%S")
    x=teensy.readline()
    print x,y