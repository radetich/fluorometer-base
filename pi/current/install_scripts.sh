#!/bin/bash
# Shebang! We're in

# run as sudo ./install_scripts.sh


# uncomment if admin user "control" is not present

# adduser control sudo

mv ./launch_python.service /etc/systemd/system/

#check this
mv ./waitnrecv.py /home/control/scripts/

systemctl enable launch_python.service
systemctl start launch_python.service 