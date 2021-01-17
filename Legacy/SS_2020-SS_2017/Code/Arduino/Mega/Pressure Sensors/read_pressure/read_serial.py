import serial
import datetime
import os.path


baud = 9600
datetime_obj = datetime.datetime.now()
print(datetime_obj)
write_to_file = None
output_file = None
serial_port = '/dev/ttyS4'


#check if file exists if it does timestamp a new file 
#if not add no time stamp

if os.path.exists('./output.txt'):
    print("FILE EXISTS ")
    now_str = datetime_obj.strftime("%d-%b-%Y (%H:%M:%S.%f)")
    write_to_file = "output-" + now_str + ".txt"
else:
    print("FILE DOES NOT EXIST")
    write_to_file = "output.txt"


#create the file
output_file = open(write_to_file, "w+")


#found flag to indicate Arduino is connected
found = False
#serial variable set to None initially
ser = None
try:
    print("Open port " + serial_port + " ... \n")
    ser = serial.Serial(serial_port, 9600, timeout=1) #create connection
    print("Serial info \n")
    print(ser)
    print("======================")
except Exception as e:
    print("Arduino not found \n")
    print(e)
    found = False

#if found is true start reading 
while found:
    print(ser.readline())
