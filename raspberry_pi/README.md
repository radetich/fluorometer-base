# Raspberry Pi Information

## Our device uses a Raspberry Pi Zero W, with Raspberry Pi OS (Debian 11) installed.

## Programs installed on the Pi:

vim (this is a convenience thing)  <br>
python3.9  <br>
python3-pip  <br>
pyserial (installed via pip)  <br>
systemd (installed via pip)  <br>
debhelper <- DEPENDENCY FOR USBMOUNT  <br>
build-essential <- DEPENDENCY FOR USBMOUNT  <br>
liblockfile-bin <- DEPENDENCY FOR USBMOUNT  <br>
liblockfile1 <- DEPENDENCY FOR USBMOUNT  <br>
lockfile-progs <- DEPENDENCY FOR USBMOUNT  <br>
pmount <- DEPENDENCY FOR USBMOUNT  <br>
radetich/usbmount (installer inside of ~/programs/usbmount. Forked from @rbrito. LEGEND!)  <br>

NOTES:

Run sudo raspi-config Interfaces -> Serial and answer "no", "yes" to the next two prompts. This allows us to communicate over hardware serial or USB as a serial, no console host.  <br>

sudo vi /boot/config.txt  <br>
    dtoverlay=disable-bt. This is not strictly necessary.  <br>

sudo vi /etc/usbmount/usbmount.conf  <br>
	FS_MOUNTOPTIONS="-fstype=vfat,uid=control,gid=control,dmask=0007,fmask=0117"  <br>
    If you wish to avoid usb devices being written to extra, it may be wise to remove the sync mount option. Not strictly necessary. See usbmount readme for more info.  <br>

sudo vi /lib/systemd/system/systemd-udevd.service  <br>
    PrivateMounts=no. This allows USBMount to mount vfat for control group properly.  <br>
