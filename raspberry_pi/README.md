# Raspberry Pi Information

## Our device uses a Raspberry Pi Zero W, with Raspberry Pi OS (Debian 11) installed.

## Programs installed on the Pi:

python3.9
python3-pip
pyserial (installed via pip)
debhelper <- DEPENDENCY FOR USBMOUNT
build-essential <- DEPENDENCY FOR USBMOUNT
liblockfile-bin <- DEPENDENCY FOR USBMOUNT
liblockfile1 <- DEPENDENCY FOR USBMOUNT
lockfile-progs <- DEPENDENCY FOR USBMOUNT
pmount <- DEPENDENCY FOR USBMOUNT
radetich/usbmount (installer inside of ~/programs/usbmount. Forked from @rbrito. LEGEND!)

NOTES:

Run sudo raspi-config Interfaces -> Serial and answer "no", "yes" to the next two prompts. This allows us to communicate over hardware serial or USB as a serial, no console host.

sudo vi /boot/config.txt
    dtoverlay=disable-bt. This is not strictly necessary.

sudo vi /etc/usbmount/usbmount.conf
	FS_MOUNTOPTIONS="-fstype=vfat,uid=control,gid=control,dmask=0007,fmask=0117"
    If you wish to avoid usb devices being written to extra, it may be wise to remove the sync mount option. Not strictly necessary. See usbmount readme for more info.

sudo vi /lib/systemd/system/systemd-udevd.service
    PrivateMounts=no. This allows USBMount to mount vfat for control group properly.
