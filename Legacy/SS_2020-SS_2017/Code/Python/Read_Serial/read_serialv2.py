import serial
import datetime
import os.path
import sys
import usb.core
import glob




def scan():
   # scan for available ports. return a list of device names.
   return glob.glob('/dev/ttyS*') + glob.glob('/dev/ttyUSB*')

for name in scan(): print(name)

